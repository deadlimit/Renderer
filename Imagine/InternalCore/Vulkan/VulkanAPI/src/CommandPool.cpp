#include "CommandPool.h"
#include "VulkanCore.h"
#include "GPU.h"
#include "GPUHandle.h"

namespace Vulkan {

	CommandPool::CommandPool(const GPUHandle& handle) : m_GPUHandleRef(handle) {}

	void CommandPool::CreateCommandPool(const GPU& GPU, int bufferAmount) {
		VkCommandPoolCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		createInfo.queueFamilyIndex = GPU.GetQueueFamilies().graphics.value();

		VKCALL(vkCreateCommandPool(m_GPUHandleRef.Get(), &createInfo, nullptr, &m_CommandPool));

		m_CommandBuffers.resize(bufferAmount);

		VkCommandBufferAllocateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		bufferInfo.commandPool = m_CommandPool;
		bufferInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		bufferInfo.commandBufferCount = bufferAmount;

		VKCALL(vkAllocateCommandBuffers(m_GPUHandleRef.Get(), &bufferInfo, m_CommandBuffers.data()));

	}

	CommandPool::~CommandPool() {
		vkDestroyCommandPool(m_GPUHandleRef.Get(), m_CommandPool, nullptr);
	}


}