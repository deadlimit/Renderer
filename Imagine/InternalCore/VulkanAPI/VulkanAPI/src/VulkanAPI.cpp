#include "VulkanAPI.h"
#include "VulkanInstance.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include "Swapchain.h"
#include "Mesh.h"

std::vector<Vertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	{{ 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
	{{ 0.5f, 0.5f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
	{{-0.5f, 0.5f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
};

std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};


void VulkanAPI::Init() {

	
	std::cout << "Hello from dll!" << std::endl;
	return;

	CompileShaders();

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	m_Window = glfwCreateWindow(800, 400, "Test", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);
	
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, OnWindowResize);

	m_Instance = new VulkanInstance(m_Window, m_AvailableFrames);

	m_GPU = m_Instance->GetDeviceContext().GPU->Get();
	m_Device = m_Instance->GetDeviceContext().Handle->Get();

	VkCommandPoolCreateInfo commandInfo{ VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
	commandInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	commandInfo.queueFamilyIndex = m_Instance->GetDeviceContext().GPU->GetQueueFamilies().graphics.value();

	VkCommandPool commandPool;
	vkCreateCommandPool(m_Device, &commandInfo, nullptr, &commandPool);

	m_MeshFactory = new MeshFactory(m_Instance->GetDeviceContext(), commandPool);

	m_CurrentFrame = 0;

	InitSyncObjects();
}


void VulkanAPI::Run() {

	Mesh& mesh = m_MeshFactory->CreateMesh(vertices, indices, MemoryType::GPU);
	
	m_Meshes.push_back(mesh);

	while (!glfwWindowShouldClose(m_Window)) {

		glfwPollEvents();
		
		for(int i = 0; i < m_Meshes.size(); ++i)
			Draw(m_Meshes[i]);

	}
}

void VulkanAPI::Draw(const Mesh& mesh) {

	vkWaitForFences(m_Device, 1, &m_InFlightFence[m_CurrentFrame], VK_TRUE, UINT64_MAX);
	vkResetFences(m_Device, 1, &m_InFlightFence[m_CurrentFrame]);

	uint32_t imageIndex;

	VkResult state = vkAcquireNextImageKHR(m_Device, m_Instance->GetSwapchain().Get(), UINT64_MAX, m_ImageAvailableSemaphore[m_CurrentFrame], nullptr, &imageIndex);

	if (state == VK_ERROR_OUT_OF_DATE_KHR) {
		UpdateSwapchain();
	} else if(state != VK_SUCCESS && state != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("Failed to aquire image");
	}

	m_Instance->RecordCommandBuffer(m_CurrentFrame, imageIndex, mesh);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &m_ImageAvailableSemaphore[m_CurrentFrame];
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_Instance->GetBuffer(m_CurrentFrame);

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &m_RenderFinishedSemaphore[m_CurrentFrame];

	VkQueue queue = m_Instance->GetGraphicsQueue();

	if (vkQueueSubmit(queue, 1, &submitInfo, m_InFlightFence[m_CurrentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &m_RenderFinishedSemaphore[m_CurrentFrame];

	VkSwapchainKHR swapChains[] = { m_Instance->GetSwapchain().Get() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;

	VkResult queueResult = vkQueuePresentKHR(m_Instance->GetPresentQueue(), &presentInfo);

	if (queueResult == VK_ERROR_OUT_OF_DATE_KHR || queueResult == VK_SUBOPTIMAL_KHR || m_WindowWasResized) {
		m_WindowWasResized = false;
		UpdateSwapchain();
	}else if (queueResult != VK_SUCCESS)
		throw std::runtime_error("Failed to present image!");

	m_CurrentFrame = (m_CurrentFrame + 1) % m_AvailableFrames;
}

void VulkanAPI::InitSyncObjects() {

	m_ImageAvailableSemaphore.resize(m_AvailableFrames);
	m_RenderFinishedSemaphore.resize(m_AvailableFrames);
	m_InFlightFence.resize(m_AvailableFrames);

	VkSemaphoreCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	
	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (int i = 0; i < m_AvailableFrames; ++i) {
		if (vkCreateSemaphore(m_Device, &createInfo, nullptr, &m_ImageAvailableSemaphore[i]) != VK_SUCCESS ||
			vkCreateSemaphore(m_Device, &createInfo, nullptr, &m_RenderFinishedSemaphore[i]) != VK_SUCCESS ||
			vkCreateFence(m_Device, &fenceInfo, nullptr, &m_InFlightFence[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create semaphores!");
		}
	}
}

void VulkanAPI::UpdateSwapchain() const {

	vkDeviceWaitIdle(m_Instance->GetDeviceContext().Handle->Get());

	m_Instance->RecreateSwapchain();
}

void VulkanAPI::CompileShaders() {
	//Needs to be awaited
	std::system("ShaderCompilation.bat");
}

void VulkanAPI::OnWindowResize(GLFWwindow* window, int width, int height) {
	reinterpret_cast<VulkanAPI*>(glfwGetWindowUserPointer(window))->m_WindowWasResized = true;
}

void VulkanAPI::Clean() {

	delete m_MeshFactory;

	vkDeviceWaitIdle(m_Device);

	for (int i = 0; i < m_AvailableFrames; ++i) {
		vkDestroySemaphore(m_Device, m_ImageAvailableSemaphore[i], nullptr);
		vkDestroySemaphore(m_Device, m_RenderFinishedSemaphore[i], nullptr);
		vkDestroyFence(m_Device, m_InFlightFence[i], nullptr);
	}

	delete m_Instance;

	glfwDestroyWindow(m_Window);
	glfwTerminate();

}