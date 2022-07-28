#pragma once

#include "VulkanCore.h"
#include <vector>
#include "DeviceContext.h"
#include "Mesh.h"

namespace Vulkan {

	struct DeviceContext;

	enum class MemoryType {
		CPU = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		GPU = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		TRANSFER_SOURCE = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		TRANSER_DESTINATION = VK_BUFFER_USAGE_TRANSFER_DST_BIT
	};


	/// <summary>
	/// BufferManager allocates and deallocates buffers, no allocation calls should be made outside of this class
	/// </summary>
	class MeshFactory {

	public:

		MeshFactory(const DeviceContext&, const VkCommandPool&);

		Mesh& CreateMesh(const std::vector<Vertex>&, const std::vector<uint16_t>&, MemoryType);

		void DestroyBuffer(std::tuple<VkBuffer, VkDeviceMemory>);

	private:

		void CopyBuffer(VkBuffer&, VkBuffer&, VkDeviceSize);

		BufferData CreateBuffer(VkDeviceSize, VkBufferUsageFlags, VkMemoryPropertyFlags);

		const DeviceContext& m_DeviceContext;
		const VkCommandPool m_CommandPool;
	};

}