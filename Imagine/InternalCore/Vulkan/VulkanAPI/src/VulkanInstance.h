#pragma once

#include "VulkanCore.h"
#include "Swapchain.h"
#include "CommandPool.h"
#include "DeviceContext.h"

namespace Vulkan {

	class VulkanDebugger;
	class RenderPass;
	class GraphicPipeline;
	class CommandPool;
	class Mesh;

	//Kanske ska ha pekaren till den riktiga GPU?

	class VulkanInstance {

	public:

		VulkanInstance(GLFWwindow*, int);
		~VulkanInstance();
	
		void RecordCommandBuffer(uint32_t, uint32_t, const Mesh&);

		const DeviceContext& GetDeviceContext() const { return m_DeviceContext; }
		const Swapchain& GetSwapchain()  { return *m_Swapchain; }
		const VkCommandBuffer& GetBuffer(uint32_t index) const { return m_GraphicsCommandPool->GetBuffer(index); }
		const VkQueue& GetGraphicsQueue() const { return m_DeviceContext.GPU->GetGraphicsQueue(); }
		const VkQueue& GetPresentQueue() const { return m_DeviceContext.GPU->GetPresentQueue(); }

		void RecreateSwapchain() const;

	private:
		void CreateInstance();
		void PickGPU();
		void CreateGPUHandle();
		void CreateRenderSurface();

	//TEMP

	private:
		//void CreateBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags, VkBuffer&, VkDeviceMemory&);
		//void CreateVertexBuffer();
		//void CopyBuffer(VkBuffer&, VkBuffer&, VkDeviceSize);

		//void CreateIndexBuffer();

		void CreateDescriptorLayout();

	private:

		const int m_FramesInFlight;

		GLFWwindow& m_Window;
		VkSurfaceKHR m_RenderSurface;
		VkInstance m_Instance;

		DeviceContext m_DeviceContext;

		Swapchain* m_Swapchain;
		RenderPass* m_RenderPass;
		GraphicPipeline* m_GraphicPipeline;

		CommandPool* m_GraphicsCommandPool;
	
		//TEMP
		VkBuffer m_VertexBuffer;
		VkBuffer m_IndexBuffer;
		VkDeviceMemory m_VertexMemoryAllocation;
		VkDeviceMemory m_IndexMemoryAllocation;

		VkDescriptorSetLayout m_DescriptorSetLayout;

		VulkanDebugger* m_Debugger;
	};

}