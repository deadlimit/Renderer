#pragma once

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"

#define SHADER_RESOURCE(x) "../InternalCore/OpenGL/Resources/Shaders/"##x

struct Vertex {
	glm::vec3 Position;

	static constexpr unsigned int Stride = sizeof(float) * 3;
};
