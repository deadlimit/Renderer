#include "GPU.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <set>
#include "Swapchain.h"
#include "GraphicPipeline.h"
#include "RenderPass.h"

void GPU::PickGPU(const VkInstance& instance) {
	uint32_t deviceCount;

	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("Failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);

	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	VkPhysicalDeviceProperties properies{};
	vkGetPhysicalDeviceProperties(devices[0], &properies);

	//I only have one GPU on this computer
	m_PhysicalDevice = devices[0];
	std::cout << "GPU: " << properies.deviceName << std::endl;

	vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &m_MemoryProperties);
}


void GPU::IdentifyQueueFamilies(const VkSurfaceKHR& surface) {

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, nullptr);

	if (queueFamilyCount == 0)
		throw std::runtime_error("GPU doesn't have any queue families");

	std::vector<VkQueueFamilyProperties> queueFamiliesProperties(queueFamilyCount);

	vkGetPhysicalDeviceQueueFamilyProperties(m_PhysicalDevice, &queueFamilyCount, queueFamiliesProperties.data());

	int i = 0;

	for (const auto& queue : queueFamiliesProperties) {
		if (queue.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT)) {

			m_QueueFamilies.graphics = i;
			m_QueueFamilies.transfer = i;
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(m_PhysicalDevice, i, surface, &presentSupport);

			if (presentSupport) {
				m_QueueFamilies.presentation = i;
			}

			break;
		}
		i++;
	}
}

void GPU::InitiateQueues(const VkDevice& device) {
	vkGetDeviceQueue(device, m_QueueFamilies.graphics.value(), 0, &graphicsQueue);
	vkGetDeviceQueue(device, m_QueueFamilies.presentation.value(), 0, &presentQueue);
	vkGetDeviceQueue(device, m_QueueFamilies.transfer.value(), 0, &transferQueue);
}

bool GPU::SupportsDeviceExtensions(std::vector<const char*>& extensions) const {
	
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);

	vkEnumerateDeviceExtensionProperties(m_PhysicalDevice, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());
	
	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

uint32_t GPU::HasMemoryProperty(uint32_t bufferMemoryRequirementBits, uint32_t requestedProperties) const {

	for (uint32_t i = 0; i < m_MemoryProperties.memoryTypeCount; ++i) {

		if (bufferMemoryRequirementBits & (1 << i) && (m_MemoryProperties.memoryTypes[i].propertyFlags & requestedProperties) == requestedProperties) {
			return i;
		}
	}

	return -1;
}

GPU::~GPU() {

}