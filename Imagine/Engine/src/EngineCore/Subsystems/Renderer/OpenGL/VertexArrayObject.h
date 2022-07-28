#pragma once
#include <vector>
#include "OpenGLCore.h"

namespace OpenGL {

	static uint32_t CreateVertexArrayObject(const std::vector<Vertex>&, const std::vector<uint32_t>&);
	static void DeleteVertexArrayObject(uint32_t);
}


