#pragma once
#include <vector>
#include "VulkanCore.h"

namespace Vulkan {

	class Swapchain;
	class GPU;

	class GPUHandle {

	public:
		GPUHandle(GPU&, VkSurfaceKHR&);
		~GPUHandle();

		void CreateHandle(const std::vector<const char*>&);

		inline const VkDevice& Get() const { return m_GPUHandle; }

	private:

		VkDevice m_GPUHandle;

		GPU& m_Owner;
		VkSurfaceKHR& m_RenderSurface;

		VkQueue m_GraphicsQueueHandle;
		VkQueue m_PresentationQueueHandle;
		VkQueue m_TransferQueueHandle;

	};

}