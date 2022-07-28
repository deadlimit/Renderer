#include "GraphicPipeline.h"
#include <fstream>
#include <stdexcept>
#include "RenderPass.h"
#include "GPUHandle.h"
#include "Vertex.h"

namespace Vulkan {

    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    GraphicPipeline::GraphicPipeline(const GPUHandle& handle) : m_GPUHandle(handle) {}

    void GraphicPipeline::CreateGraphicPipeline(RenderPass& renderPass, const VkExtent2D& extent, const VkDescriptorSetLayout& descriptorLayout) {

        VkPipelineDynamicStateCreateInfo dynamicState{};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
        dynamicState.pDynamicStates = dynamicStates.data();

        VkPipelineShaderStageCreateInfo vertexCreateInfo{};
        vertexCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        vertexCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        vertexCreateInfo.module = shaderModules[SHADER::VERTEX];
        vertexCreateInfo.pName = "main"; //Entry point for shader

        VkPipelineShaderStageCreateInfo fragmentCreateInfo{};
        fragmentCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        fragmentCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        fragmentCreateInfo.module = shaderModules[SHADER::FRAGMENT];
        fragmentCreateInfo.pName = "main"; //Entry point for shader

        VkPipelineShaderStageCreateInfo stages[] = { vertexCreateInfo, fragmentCreateInfo };

        VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.pVertexBindingDescriptions = &Vertex::BindingDescription();
        vertexInputInfo.vertexAttributeDescriptionCount = 3;
        vertexInputInfo.pVertexAttributeDescriptions = Vertex::AttributeDescription().data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        UpdateViewport(extent);

        VkPipelineViewportStateCreateInfo viewportState{};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &m_Viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &m_Scissor;

        VkPipelineRasterizationStateCreateInfo rasterizer{};
        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizer.depthClampEnable = VK_FALSE;
        rasterizer.rasterizerDiscardEnable = VK_FALSE;
        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        rasterizer.lineWidth = 1.0f;
        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
        rasterizer.depthBiasEnable = VK_FALSE;
        rasterizer.depthBiasConstantFactor = 0.0f;
        rasterizer.depthBiasClamp = 0.0f;
        rasterizer.depthBiasSlopeFactor = 0.0f;

        VkPipelineMultisampleStateCreateInfo multisampling{};
        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multisampling.sampleShadingEnable = VK_FALSE;
        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        multisampling.minSampleShading = 1.0f;
        multisampling.pSampleMask = nullptr;
        multisampling.alphaToCoverageEnable = VK_FALSE;
        multisampling.alphaToOneEnable = VK_FALSE;


        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;
        colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
        colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
        colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
        colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

        VkPipelineColorBlendStateCreateInfo colorBlending{};
        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        colorBlending.logicOpEnable = VK_FALSE;
        colorBlending.logicOp = VK_LOGIC_OP_COPY;
        colorBlending.attachmentCount = 1;
        colorBlending.pAttachments = &colorBlendAttachment;
        colorBlending.blendConstants[0] = 0.0f;
        colorBlending.blendConstants[1] = 0.0f;
        colorBlending.blendConstants[2] = 0.0f;
        colorBlending.blendConstants[3] = 0.0f;

        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
        pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutCreateInfo.setLayoutCount = 1;
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;
        pipelineLayoutCreateInfo.setLayoutCount = 1;
        pipelineLayoutCreateInfo.pSetLayouts = &descriptorLayout;

        const VkDevice& device = m_GPUHandle.Get();

        VKCALL(vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &pipelineLayout));

        VkGraphicsPipelineCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        createInfo.stageCount = 2;
        createInfo.pStages = stages;
        createInfo.pVertexInputState = &vertexInputInfo;
        createInfo.pInputAssemblyState = &inputAssembly;
        createInfo.pColorBlendState = &colorBlending;
        createInfo.pRasterizationState = &rasterizer;
        createInfo.pDynamicState = nullptr;
        createInfo.pMultisampleState = &multisampling;
        createInfo.pDepthStencilState = nullptr;
        createInfo.pViewportState = &viewportState;
        createInfo.pNext = nullptr;
        createInfo.pTessellationState = nullptr;
        createInfo.layout = pipelineLayout;
        createInfo.renderPass = renderPass.GetRenderPass();
        createInfo.subpass = 0; //INDEX TILL SUBPASS, INTE NOLL
        createInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
        createInfo.basePipelineIndex = -1;
        createInfo.pDynamicState = &dynamicState;

        VKCALL(vkCreateGraphicsPipelines(m_GPUHandle.Get(), nullptr, 1, &createInfo, nullptr, &m_GraphicsPipeline));

        vkDestroyShaderModule(device, shaderModules[SHADER::VERTEX], nullptr);
        vkDestroyShaderModule(device, shaderModules[SHADER::FRAGMENT], nullptr);

    }

    static std::vector<char> ReadFile(const std::string& filename) {

        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;

    }

    void GraphicPipeline::UpdateViewport(VkExtent2D newExtent) {

        m_Viewport.x = 0.0f;
        m_Viewport.y = 0.0f;
        m_Viewport.width = (float)newExtent.width;
        m_Viewport.height = (float)newExtent.height;
        m_Viewport.minDepth = 0.0f;
        m_Viewport.maxDepth = 1.0f;

        m_Scissor.offset = { 0, 0 };
        m_Scissor.extent = newExtent;
    }



    VkShaderModule GraphicPipeline::CreateShaderModule(const std::vector<char>& code) {

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkShaderModule shaderModule;

        VkResult result = vkCreateShaderModule(m_GPUHandle.Get(), &createInfo, nullptr, &shaderModule);

        if (result != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }

        return shaderModule;

    }

    GraphicPipeline::~GraphicPipeline() {
        vkDestroyPipeline(m_GPUHandle.Get(), m_GraphicsPipeline, nullptr);
        vkDestroyPipelineLayout(m_GPUHandle.Get(), pipelineLayout, nullptr);
    }

    void GraphicPipeline::LoadShader(SHADER shaderType, const std::string& path) {

        std::vector<char> code = ReadFile(path.c_str());

        shaderModules[shaderType] = CreateShaderModule(code);
    }

}