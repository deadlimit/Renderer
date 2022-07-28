#include "VulkanInstance.h"
#include <iostream>
#include "VulkanDebugger.h"
#include "GPUHandle.h"
#include "Swapchain.h"
#include "RenderPass.h"
#include "GraphicPipeline.h"
#include "Vertex.h"
#include "Mesh.h"

namespace Vulkan {

	std::vector<const char*> DEVICE_EXTENSIONS = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME,
	};

	VulkanInstance::VulkanInstance(GLFWwindow* targetWindow, int framesInFlight) : m_Instance(nullptr), m_Debugger(nullptr), m_Window(*targetWindow), m_FramesInFlight(framesInFlight) {

		CreateInstance();

		CreateRenderSurface();

		PickGPU();

		CreateGPUHandle();

		m_DeviceContext.GPU->InitiateQueues(m_DeviceContext.Handle->Get());

		m_Swapchain = new Swapchain(*m_DeviceContext.Handle);

		if (!m_Swapchain->IsAdequate(m_DeviceContext.GPU->Get(), m_RenderSurface))
			throw std::runtime_error("Swapchain not compatible with GPU");

		m_Swapchain->CreateSwapchain(*targetWindow, m_RenderSurface, m_DeviceContext.GPU->GetQueueFamilies());

		m_RenderPass = new RenderPass(*m_DeviceContext.Handle);
		m_RenderPass->CreateRenderPass(m_Swapchain->GetFormat());

		CreateDescriptorLayout();

		m_GraphicPipeline = new GraphicPipeline(*m_DeviceContext.Handle);
		m_GraphicPipeline->LoadShader(SHADER::VERTEX, "../Resources/Shaders/Compiled/Test.vert.spv");
		m_GraphicPipeline->LoadShader(SHADER::FRAGMENT, "../Resources/Shaders/Compiled/Test.frag.spv");
		m_GraphicPipeline->CreateGraphicPipeline(*m_RenderPass, m_Swapchain->GetExtent(), m_DescriptorSetLayout);

		m_Swapchain->CreateFramebuffers(*m_RenderPass);

		m_GraphicsCommandPool = new CommandPool(*m_DeviceContext.Handle);
		m_GraphicsCommandPool->CreateCommandPool(*m_DeviceContext.GPU, framesInFlight);

	}

	void VulkanInstance::RecordCommandBuffer(uint32_t currentFrame, uint32_t imageIndex, const Mesh& model) {

		const VkCommandBuffer& currentCommandBuffer = m_GraphicsCommandPool->GetBuffer(currentFrame);

		vkResetCommandBuffer(currentCommandBuffer, 0);

		VkCommandBufferBeginInfo recordInfo{};
		recordInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		recordInfo.flags = 0;
		recordInfo.pInheritanceInfo = nullptr;

		VKCALL(vkBeginCommandBuffer(currentCommandBuffer, &recordInfo));

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_RenderPass->GetRenderPass();
		renderPassInfo.framebuffer = m_Swapchain->GetFramebufferAtIndex(imageIndex);
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_Swapchain->GetExtent();

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(currentCommandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(currentCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicPipeline->Get());
		vkCmdSetViewport(currentCommandBuffer, 0, 1, &m_GraphicPipeline->GetViewport());
		vkCmdSetScissor(currentCommandBuffer, 0, 1, &m_GraphicPipeline->GetScissor());

		VkBuffer vertexBuffers[] = { m_VertexBuffer };

		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(currentCommandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(currentCommandBuffer, m_IndexBuffer, 0, VK_INDEX_TYPE_UINT16);

		vkCmdDrawIndexed(currentCommandBuffer, model.GetMeshData().Indices.size(), 1, 0, 0, 0);

		vkCmdEndRenderPass(currentCommandBuffer);

		VKCALL(vkEndCommandBuffer(currentCommandBuffer));
	}


	void VulkanInstance::RecreateSwapchain() const {
		m_Swapchain->Clean();
		m_Swapchain->CreateSwapchain(m_Window, m_RenderSurface, m_DeviceContext.GPU->GetQueueFamilies());
		m_GraphicPipeline->UpdateViewport(m_Swapchain->GetExtent());
		m_Swapchain->CreateFramebuffers(*m_RenderPass);
	}

	void VulkanInstance::CreateInstance() {
		std::cout << "Creating instance" << std::endl;

		VkApplicationInfo applicationInfo{};

		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pApplicationName = "Vulkan";
		applicationInfo.pEngineName = "Vulkan";
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.apiVersion = VK_API_VERSION_1_0;


		VkInstanceCreateInfo instanceCreateInfo{};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &applicationInfo;

		if (enableValidationLayers) {

			m_Debugger = new VulkanDebugger();

			instanceCreateInfo.enabledLayerCount = m_Debugger->GetValidationLayers().size();
			instanceCreateInfo.ppEnabledLayerNames = m_Debugger->GetValidationLayers().data();
		}

		uint32_t glfwExtensionCount = 0;

		const char** extensionNames = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		instanceCreateInfo.enabledExtensionCount = glfwExtensionCount;
		instanceCreateInfo.ppEnabledExtensionNames = extensionNames;


		VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_Instance);

		if (result != VK_SUCCESS) {
			std::cout << "ERROR: Failed to create instance" << std::endl;
			throw std::runtime_error("");
		}
	}

	void VulkanInstance::PickGPU() {
		m_DeviceContext.GPU = new GPU();
		m_DeviceContext.GPU->PickGPU(m_Instance);

		if (!m_DeviceContext.GPU->SupportsDeviceExtensions(DEVICE_EXTENSIONS))
			throw std::runtime_error("Doesnt support extentions");

		m_DeviceContext.GPU->IdentifyQueueFamilies(m_RenderSurface);

	}

	void VulkanInstance::CreateGPUHandle() {
		m_DeviceContext.Handle = new GPUHandle(*m_DeviceContext.GPU, m_RenderSurface);
		m_DeviceContext.Handle->CreateHandle(DEVICE_EXTENSIONS);
	}

	//It's GLFW-specific, that's why it's here
	void VulkanInstance::CreateRenderSurface() {
		if (glfwCreateWindowSurface(m_Instance, &m_Window, nullptr, &m_RenderSurface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	/*

	void VulkanInstance::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryFlags, VkBuffer& buffer, VkDeviceMemory& memoryAllocation) {

		VkBufferCreateInfo createInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
		createInfo.usage = usageFlags;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.size = size;

		uint32_t si = sizeof Vertex;

		VKCALL(vkCreateBuffer(m_GPUHandle->Get(), &createInfo, nullptr, &buffer));

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(m_GPUHandle->Get(), buffer, &memoryRequirements);

		uint32_t allocationMemoryType = m_DeviceContext.GPU->HasMemoryProperty(memoryRequirements.memoryTypeBits, memoryFlags);

		if (allocationMemoryType == -1)
			throw std::runtime_error("Required memory type not supported on this GPU");

		VkMemoryAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
		allocateInfo.allocationSize = memoryRequirements.size;
		allocateInfo.memoryTypeIndex = allocationMemoryType;

		VKCALL(vkAllocateMemory(m_GPUHandle->Get(), &allocateInfo, nullptr, &memoryAllocation));

		VKCALL(vkBindBufferMemory(m_GPUHandle->Get(), buffer, memoryAllocation, 0));

	}
	*/
	/*
	void VulkanInstance::CreateVertexBuffer() {

		VkDeviceSize size = sizeof Vertex * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMemory;

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);

		void* data;
		vkMapMemory(m_DeviceContext.Handle->Get(), stagingMemory, 0, size, 0, &data);
		memcpy(data, vertices.data(), size);
		vkUnmapMemory(m_DeviceContext.Handle->Get(), stagingMemory);

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_VertexBuffer, m_VertexMemoryAllocation);

		CopyBuffer(stagingBuffer, m_VertexBuffer, size);
		vkDestroyBuffer(m_DeviceContext.Handle->Get(), stagingBuffer, nullptr);
		vkFreeMemory(m_DeviceContext.Handle->Get(), stagingMemory, nullptr);

	}

	void VulkanInstance::CopyBuffer(VkBuffer& source, VkBuffer& destination, VkDeviceSize size) {

		VkCommandBufferAllocateInfo createInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		createInfo.commandPool = m_GraphicsCommandPool->GetCommandPool();
		createInfo.commandBufferCount = 1;
		createInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		VkCommandBuffer commandBuffer;
		VKCALL(vkAllocateCommandBuffers(m_DeviceContext.Handle->Get(), &createInfo, &commandBuffer));

		VkCommandBufferBeginInfo recordInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		recordInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &recordInfo);

		VkBufferCopy copyInfo{};
		copyInfo.size = size;

		vkCmdCopyBuffer(commandBuffer, source, destination, 1, &copyInfo);

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_DeviceContext.GPU->GetTransferQueue(), 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(m_DeviceContext.GPU->GetTransferQueue());

		vkFreeCommandBuffers(m_DeviceContext.Handle->Get(), m_GraphicsCommandPool->GetCommandPool(), 1, &commandBuffer);

	}


	void VulkanInstance::CreateIndexBuffer() {

		VkDeviceSize size = sizeof indices[0] * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingMemory;

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);

		void* data;
		vkMapMemory(m_DeviceContext.Handle->Get(), stagingMemory, 0, size, 0, &data);
		memcpy(data, indices.data(), size);
		vkUnmapMemory(m_DeviceContext.Handle->Get(), stagingMemory);

		CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_IndexBuffer, m_IndexMemoryAllocation);

		CopyBuffer(stagingBuffer, m_IndexBuffer, size);
		vkDestroyBuffer(m_DeviceContext.Handle->Get(), stagingBuffer, nullptr);
		vkFreeMemory(m_DeviceContext.Handle->Get(), stagingMemory, nullptr);
	}

	*/

	void VulkanInstance::CreateDescriptorLayout() {

		VkDescriptorSetLayoutBinding layoutBinding{};
		layoutBinding.binding = 0;
		layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBinding.descriptorCount = 1;
		layoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

		VkDescriptorSetLayoutCreateInfo createInfo{ VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO };
		createInfo.pBindings = &layoutBinding;
		createInfo.bindingCount = 1;

		VKCALL(vkCreateDescriptorSetLayout(m_DeviceContext.Handle->Get(), &createInfo, nullptr, &m_DescriptorSetLayout));
	}

	VulkanInstance::~VulkanInstance() {

		vkDestroyDescriptorSetLayout(m_DeviceContext.Handle->Get(), m_DescriptorSetLayout, nullptr);

		vkFreeMemory(m_DeviceContext.Handle->Get(), m_IndexMemoryAllocation, nullptr);
		vkDestroyBuffer(m_DeviceContext.Handle->Get(), m_IndexBuffer, nullptr);

		vkFreeMemory(m_DeviceContext.Handle->Get(), m_VertexMemoryAllocation, nullptr);
		vkDestroyBuffer(m_DeviceContext.Handle->Get(), m_VertexBuffer, nullptr);

		delete m_GraphicsCommandPool;
		delete m_Debugger;
		delete m_GraphicPipeline;
		delete m_RenderPass;
		delete m_Swapchain;

		vkDestroySurfaceKHR(m_Instance, m_RenderSurface, nullptr);
		vkDestroyInstance(m_Instance, nullptr);
	}

}