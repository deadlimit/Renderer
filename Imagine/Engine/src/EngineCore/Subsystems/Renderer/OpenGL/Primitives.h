#pragma once

#include "OpenGLCore.h"
#include <vector>

namespace Renderer {

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indicies;
	};
	
	MeshData Square();
	MeshData Cube();
	MeshData Triangle();

}

