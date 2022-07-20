#pragma once
#include "VulkanCore.h"
#include <vector>
#include <unordered_map>

namespace Vulkan {

	class Swapchain;
	class RenderPass;
	class GPUHandle;

	enum class SHADER {
		VERTEX,
		FRAGMENT
	};

	class GraphicPipeline {

	public:

		GraphicPipeline(const GPUHandle&);
		~GraphicPipeline();

		void LoadShader(SHADER, const std::string&);

		void UpdateViewport(VkExtent2D);

		void CreateGraphicPipeline(RenderPass&, const VkExtent2D&, const VkDescriptorSetLayout&);

		inline const VkPipeline& Get() const { return m_GraphicsPipeline; }
		inline const VkViewport& GetViewport() const { return m_Viewport; }
		inline const VkRect2D& GetScissor() const { return m_Scissor; }

	private:

		VkShaderModule CreateShaderModule(const std::vector<char>&);

	private:

		VkViewport m_Viewport;
		VkRect2D m_Scissor;

		VkPipelineLayout pipelineLayout;
		VkPipeline m_GraphicsPipeline;

		std::unordered_map<SHADER, VkShaderModule> shaderModules;

		const GPUHandle& m_GPUHandle;

	};


}
