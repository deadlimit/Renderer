#pragma once
#include "VulkanCore.h"
#include <optional>
#include <vector>

class Swapchain;
class Pipeline;
class RenderPass;

class GPU {

public:
	GPU() = default;
	~GPU();

	void PickGPU(const VkInstance&);
	void IdentifyQueueFamilies(const VkSurfaceKHR&);
	void InitiateQueues(const VkDevice&);
	bool SupportsDeviceExtensions(std::vector<const char*>&) const;
	
	inline const VkPhysicalDevice& Get() const { return m_PhysicalDevice; }

	const QueueFamilies& GetQueueFamilies() const { return m_QueueFamilies; }
	const VkQueue& GetGraphicsQueue() const { return graphicsQueue; }
	const VkQueue& GetPresentQueue() const { return presentQueue; }
	const VkQueue& GetTransferQueue() const { return transferQueue; }

	uint32_t HasMemoryProperty(uint32_t, uint32_t) const;

private:
	
	VkPhysicalDevice m_PhysicalDevice;
	QueueFamilies m_QueueFamilies;
	VkPhysicalDeviceMemoryProperties m_MemoryProperties;

	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkQueue transferQueue;

	Pipeline* m_GraphicsPipeline;
	RenderPass* m_RenderPass;
;};
