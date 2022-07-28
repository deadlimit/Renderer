#pragma once

#include <vector>
#include "VulkanCore.h"


namespace Vulkan {

	struct BufferData {
		VkBuffer buffer;
		VkDeviceMemory allocation;
	};

	class Mesh {

	public:
		Mesh(const MeshData&, const BufferData&);
		~Mesh();

		const MeshData& GetMeshData() const { return m_MeshData; }
		const BufferData& GetBufferData() const { return m_BufferData; }

	private:

		uint32_t ID;

		MeshData m_MeshData;
		BufferData m_BufferData;
	};

}