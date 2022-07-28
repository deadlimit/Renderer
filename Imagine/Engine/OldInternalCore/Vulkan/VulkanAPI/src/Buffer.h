#pragma once

#include "VulkanCore.h"

namespace Vulkan {

	class GPU;
	class CommandPool;

	class Buffer {

	public:

		Buffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags);

		//void CopyBuffer(VkBuffer&, VkBuffer&, VkDeviceSize, const CommandPool&, const DeviceContext&);

	private:

		VkBuffer m_Buffer;
		VkDeviceMemory m_Allocation;
	};

}