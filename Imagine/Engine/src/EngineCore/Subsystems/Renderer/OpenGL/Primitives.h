#pragma once

#include "OpenGLCore.h"
#include <vector>

namespace OpenGL {

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indicies;
	};
	
	MeshData Square();
	MeshData Triangle();

}

