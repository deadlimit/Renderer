#include "Mesh.h"

namespace Vulkan {

	Mesh::Mesh(const MeshData& meshData, const BufferData& bufferData) : ID(reinterpret_cast<uint32_t>(this)), m_MeshData(meshData), m_BufferData(bufferData) {}

	Mesh::~Mesh() {}

}
