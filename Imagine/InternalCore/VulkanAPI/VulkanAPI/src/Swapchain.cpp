#include "Swapchain.h"
#include <limits>
#include <algorithm> 
#include <cstdint> 
#include <stdexcept>
#include "GPU.h"
#include "RenderPass.h"
#include "GPUHandle.h"


Swapchain::Swapchain(const GPUHandle& gpuHandle) : m_GPUHandle(gpuHandle), m_SwapchainActive(false) {}


void Swapchain::CreateSwapchain(GLFWwindow& window, const VkSurfaceKHR& renderSurface, const QueueFamilies& queueFamilies) {

	const VkDevice& device = m_GPUHandle.Get();

	VkSurfaceFormatKHR format = PickSurfaceFormat();
	VkPresentModeKHR presentMode = PickPresentMode();
	m_Extent = PickSwapExtent(window);

	uint32_t imageCount = swapchainDetails.capabilities.minImageCount + 1;

	if (swapchainDetails.capabilities.maxImageCount > 0 && imageCount > swapchainDetails.capabilities.maxImageCount) {
		imageCount = swapchainDetails.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = m_ImageFormat = format.format;
	createInfo.imageColorSpace = format.colorSpace;
	createInfo.imageExtent = m_Extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.surface = renderSurface;
	
	
	uint32_t queueFamilyIndices[] = { queueFamilies.graphics.value(), queueFamilies.presentation.value() };

	if (queueFamilies.graphics != queueFamilies.presentation) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;

	}

	createInfo.preTransform = swapchainDetails.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.clipped = VK_TRUE; //clip pixels not showing
	createInfo.oldSwapchain = VK_NULL_HANDLE;


	VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_Swapchain);

	if (result != VK_SUCCESS)
		throw std::runtime_error("Swapchain could not be created");

	//Images has been created, handles are now available

	vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, nullptr);
	m_Images.resize(imageCount);
	vkGetSwapchainImagesKHR(device, m_Swapchain, &imageCount, m_Images.data());

	CreateImageViews();

	if(m_SwapchainActive == false)
		m_SwapchainActive = true;
}

VkPresentModeKHR Swapchain::PickPresentMode() {

	for (const auto& mode : swapchainDetails.presentModes) {

		if (mode == VK_PRESENT_MODE_MAILBOX_KHR)
			return mode;

	}

	return VK_PRESENT_MODE_FIFO_KHR;

}

VkExtent2D Swapchain::PickSwapExtent(GLFWwindow& window) {

		//if (swapchainDetails.capabilities.currentExtent.width != (std::numeric_limits<uint32_t>::max)())
		//return swapchainDetails.capabilities.currentExtent;
	//else {
	int width, height;

	glfwGetFramebufferSize(&window, &width, &height);

	return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
//	}
}

void Swapchain::CreateImageViews() {

	m_ImageViews.resize(m_Images.size());

	for (int i = 0; i < m_ImageViews.size(); ++i) {

		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = m_Images[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_ImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		VkResult result = vkCreateImageView(m_GPUHandle.Get(), &createInfo, nullptr, &m_ImageViews[i]);

		if (result != VK_SUCCESS) {
			throw std::runtime_error("Could not create image view");
		}
	}
}

void Swapchain::CreateFramebuffers(RenderPass& renderpass) {

	m_Framebuffers.resize(m_ImageViews.size());

	for (int i = 0; i < m_ImageViews.size(); ++i) {

		VkFramebufferCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.renderPass = renderpass.GetRenderPass();
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = &m_ImageViews[i];
		createInfo.width = m_Extent.width;
		createInfo.height = m_Extent.height;
		createInfo.layers = 1;

		VkResult result = vkCreateFramebuffer(m_GPUHandle.Get(), &createInfo, nullptr, &m_Framebuffers[i]);

		if (result != VK_SUCCESS)
			throw std::runtime_error("Failed to create framebuffer");
	}
}

const VkFramebuffer& Swapchain::GetFramebufferAtIndex(uint32_t index) {
	return m_Framebuffers[index];
}

/// <summary>
/// Destroys framebuffers, imageviews and swapchain, use for deleting or recreating the swapchain
/// </summary>
void Swapchain::Clean() const {

	const VkDevice& device = m_GPUHandle.Get();

	for (int i = 0; i < m_Framebuffers.size(); ++i) {
		vkDestroyFramebuffer(device, m_Framebuffers[i], nullptr);
	}


	for (int i = 0; i < m_ImageViews.size(); ++i) {
		vkDestroyImageView(device, m_ImageViews[i], nullptr);
	}

	vkDestroySwapchainKHR(device, m_Swapchain, nullptr);

}

VkSurfaceFormatKHR Swapchain::PickSurfaceFormat() {
	for (const auto& format : swapchainDetails.formats) {
		if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return format;
		}
	}

	return swapchainDetails.formats[0];
}

bool Swapchain::IsAdequate(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) {

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &swapchainDetails.capabilities);

	uint32_t formatCount = 0;

	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount > 0) {
		swapchainDetails.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, swapchainDetails.formats.data());
	}

	uint32_t presentModeCount = 0;

	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount > 0) {
		swapchainDetails.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, swapchainDetails.presentModes.data());
	}

	return !swapchainDetails.Empty();
}



const VkExtent2D& Swapchain::GetExtent() const {
	return m_Extent;
}

const VkFormat& Swapchain::GetFormat() const {
	return m_ImageFormat;
}


Swapchain::~Swapchain() {
	Clean();
}