#pragma once

#include "OpenGLCore.h"
#include <vector>

namespace Renderer {

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indicies;
	};
	
	inline const MeshData Square = {
		//vertices
		{{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
		{{ 0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}},
		//indicies
		{0, 1, 2, 2, 3, 0 }
	};

}

