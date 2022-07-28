#include "GPUHandle.h"
#include <set>
#include <stdexcept>
#include "Swapchain.h"
#include "GPU.h"

namespace Vulkan {

	GPUHandle::GPUHandle(GPU& owner, VkSurfaceKHR& renderSurface) : m_Owner(owner), m_RenderSurface(renderSurface) {}


	void GPUHandle::CreateHandle(const std::vector<const char*>& requiredExtensions) {

		VkPhysicalDeviceFeatures deviceFeatures{};

		std::vector<VkDeviceQueueCreateInfo> createInfos;

		std::set<uint32_t> uniqueQueueFamilies = { m_Owner.GetQueueFamilies().graphics.value(), m_Owner.GetQueueFamilies().presentation.value() };

		for (const uint32_t& queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo deviceQueueCreateInfo{};
			deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			deviceQueueCreateInfo.queueFamilyIndex = queueFamily;
			deviceQueueCreateInfo.queueCount = 1;
			float queuePriority = 1.0f;
			deviceQueueCreateInfo.pQueuePriorities = &queuePriority;

			createInfos.push_back(deviceQueueCreateInfo);
		}

		VkDeviceCreateInfo logicalDeviceCreateInfo{};

		logicalDeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		logicalDeviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(createInfos.size());
		logicalDeviceCreateInfo.pQueueCreateInfos = createInfos.data();
		logicalDeviceCreateInfo.pEnabledFeatures = &deviceFeatures;
		logicalDeviceCreateInfo.enabledLayerCount = 0;
		logicalDeviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		logicalDeviceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();


		VkResult result = vkCreateDevice(m_Owner.Get(), &logicalDeviceCreateInfo, nullptr, &m_GPUHandle);

		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to create GPU handle");
		}

		vkGetDeviceQueue(m_GPUHandle, m_Owner.GetQueueFamilies().graphics.value(), 0, &m_GraphicsQueueHandle);
		vkGetDeviceQueue(m_GPUHandle, m_Owner.GetQueueFamilies().presentation.value(), 0, &m_PresentationQueueHandle);
		vkGetDeviceQueue(m_GPUHandle, m_Owner.GetQueueFamilies().transfer.value(), 0, &m_TransferQueueHandle);

	}

	GPUHandle::~GPUHandle() {
		vkDestroyDevice(m_GPUHandle, nullptr);
	}

}