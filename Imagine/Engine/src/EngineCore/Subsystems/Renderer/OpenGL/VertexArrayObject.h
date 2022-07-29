#pragma once
#include "OpenGLCore.h"
#include <vector>

namespace OpenGL {

	void CreateVertexArrayObject(const std::vector<Vertex>&, const std::vector<uint32_t>&, uint32_t&);
	void DeleteVertexArrayObject(uint32_t&);
}


