#include "Primitives.h"

namespace Renderer {



	MeshData Triangle() {
		return	{{{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.0f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
		{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},},
		{0, 1, 2} };
	}

}