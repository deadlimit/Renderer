#pragma once
#include "VulkanCore.h"
#include <vector>

struct SwapchainDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;

	bool Empty() {
		return formats.empty() && presentModes.empty();
	}
};

class GPUHandle;
class RenderPass;

class Swapchain { 

public:
	Swapchain(const GPUHandle&);
	~Swapchain();

	inline const VkSwapchainKHR& Get() const { return m_Swapchain; }

	void CreateSwapchain(GLFWwindow& window, const VkSurfaceKHR&, const QueueFamilies&);

	const VkExtent2D& GetExtent() const;
	const VkFormat& GetFormat() const;

	bool IsAdequate(const VkPhysicalDevice&, const VkSurfaceKHR&);
	
	void CreateFramebuffers(RenderPass&);
	
	const VkFramebuffer& GetFramebufferAtIndex(uint32_t);
	
	void Clean() const;

private:

	VkSurfaceFormatKHR PickSurfaceFormat();
	VkPresentModeKHR PickPresentMode();
	VkExtent2D PickSwapExtent(GLFWwindow&);
	void CreateImageViews();

private:

	bool m_SwapchainActive;

	std::vector<VkImage> m_Images;
	std::vector<VkImageView> m_ImageViews;
	std::vector<VkFramebuffer> m_Framebuffers;

	SwapchainDetails swapchainDetails; //bra att ha

	VkSurfaceFormatKHR m_SurfaceFormat;

	VkFormat m_ImageFormat;
	VkExtent2D m_Extent;

	VkSwapchainKHR m_Swapchain;
	const GPUHandle& m_GPUHandle;

};

