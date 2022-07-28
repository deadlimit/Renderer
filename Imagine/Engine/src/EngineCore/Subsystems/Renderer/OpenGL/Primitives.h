#pragma once

#include <vector>
#include "OpenGLCore.h"

namespace OpenGL {

	struct MeshData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indicies;
	};
	
	MeshData Square();
	MeshData Triangle();

}

