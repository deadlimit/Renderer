#pragma once
#include "OpenGLCore.h"
#include <vector>

namespace Renderer {

	void CreateVertexArrayObject(const std::vector<Vertex>&, const std::vector<uint32_t>&, uint32_t&);
	void DeleteVertexArrayObject(uint32_t&);
}


