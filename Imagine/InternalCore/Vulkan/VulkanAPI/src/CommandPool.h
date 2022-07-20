#pragma once

#include <vector>
#include "VulkanCore.h"

namespace Vulkan {

	class GPU;
	class GPUHandle;

	class CommandPool {

	public:

		CommandPool(const GPUHandle&);
		~CommandPool();

		void CreateCommandPool(const GPU&, int);

		inline const VkCommandBuffer& GetBuffer(uint32_t index) const { return m_CommandBuffers[index]; }

		inline const VkCommandPool& GetCommandPool() const { return m_CommandPool; }

	private:

		VkCommandPool m_CommandPool;

		std::vector<VkCommandBuffer> m_CommandBuffers;

		const GPUHandle& m_GPUHandleRef;

	};

}