#pragma once

#include "VulkanCore.h"

class GPUHandle;

class RenderPass {
	
public:
	RenderPass(const GPUHandle&);
	~RenderPass();


	void CreateRenderPass(VkFormat);

	VkRenderPass& GetRenderPass();

private:

	VkRenderPass m_RenderPass;

	const GPUHandle& m_GPUHandle;

};

