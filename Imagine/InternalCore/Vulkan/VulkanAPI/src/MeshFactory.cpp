#include "MeshFactory.h"
#include "DeviceContext.h"

namespace Vulkan {

	MeshFactory::MeshFactory(const DeviceContext& deviceContext, const VkCommandPool& commandPool) : m_DeviceContext(deviceContext), m_CommandPool(commandPool) {}

	Mesh& MeshFactory::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<uint16_t>& indices, MemoryType memoryType) {


		MeshData meshData;
		meshData.Vertices = vertices;
		meshData.Indices = indices;


		BufferData bufferData;

		uint32_t size = meshData.Size();

		switch (memoryType) {
		case MemoryType::CPU:
			break;
		case MemoryType::GPU:
			//create staging buffer
			BufferData stagingData = CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

			//move data into staging buffer
			void* data;
			vkMapMemory(m_DeviceContext.Handle->Get(), stagingData.allocation, 0, size, 0, &data);
			memcpy(data, meshData.Vertices.data(), size);
			vkUnmapMemory(m_DeviceContext.Handle->Get(), stagingData.allocation);

			//create buffer that will receive staging buffer data
			bufferData = CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);;

			//move data from 
			CopyBuffer(stagingData.buffer, bufferData.buffer, size);

			//Delete staging buffer
			vkDestroyBuffer(m_DeviceContext.Handle->Get(), stagingData.buffer, nullptr);
			vkFreeMemory(m_DeviceContext.Handle->Get(), stagingData.allocation, nullptr);
			break;

		default:
			throw std::runtime_error("Undefined memoryType");
		}


		Mesh mesh(meshData, bufferData);

		return mesh;
	}

	BufferData MeshFactory::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryFlags) {

		VkBufferCreateInfo createInfo{ VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
		createInfo.usage = usageFlags;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.size = size;

		VkBuffer newBuffer;

		VKCALL(vkCreateBuffer(m_DeviceContext.Handle->Get(), &createInfo, nullptr, &newBuffer));

		VkMemoryRequirements memoryRequirements;
		vkGetBufferMemoryRequirements(m_DeviceContext.Handle->Get(), newBuffer, &memoryRequirements);

		uint32_t allocationMemoryType = m_DeviceContext.GPU->HasMemoryProperty(memoryRequirements.memoryTypeBits, memoryFlags);

		if (allocationMemoryType == -1)
			throw std::runtime_error("Required memory type not supported on this GPU");

		VkMemoryAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
		allocateInfo.allocationSize = memoryRequirements.size;
		allocateInfo.memoryTypeIndex = allocationMemoryType;

		VkDeviceMemory allocation;

		VKCALL(vkAllocateMemory(m_DeviceContext.Handle->Get(), &allocateInfo, nullptr, &allocation));

		VKCALL(vkBindBufferMemory(m_DeviceContext.Handle->Get(), newBuffer, allocation, 0));

		return { newBuffer, allocation };
	}

	void MeshFactory::DestroyBuffer(std::tuple<VkBuffer, VkDeviceMemory>) {
	}

	void MeshFactory::CopyBuffer(VkBuffer& source, VkBuffer& destination, VkDeviceSize size) {

		//Create info about command buffers
		VkCommandBufferAllocateInfo allocateInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
		allocateInfo.commandPool = m_CommandPool;
		allocateInfo.commandBufferCount = 1;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

		//Allocate memory for command buffer
		VkCommandBuffer commandBuffer;
		VKCALL(vkAllocateCommandBuffers(m_DeviceContext.Handle->Get(), &allocateInfo, &commandBuffer));

		VkCommandBufferBeginInfo commandBeginInfo{ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
		commandBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		//Start record copy commands
		vkBeginCommandBuffer(commandBuffer, &commandBeginInfo);

		VkBufferCopy copyInfo{};
		copyInfo.size = size;

		//This is the copy command
		vkCmdCopyBuffer(commandBuffer, source, destination, 1, &copyInfo);

		//END
		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo commandSubmitInfo{ VK_STRUCTURE_TYPE_SUBMIT_INFO };
		commandSubmitInfo.commandBufferCount = 1;
		commandSubmitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(m_DeviceContext.GPU->GetTransferQueue(), 1, &commandSubmitInfo, nullptr);
		vkQueueWaitIdle(m_DeviceContext.GPU->GetTransferQueue());

		vkFreeCommandBuffers(m_DeviceContext.Handle->Get(), m_CommandPool, 1, &commandBuffer);

	}

}