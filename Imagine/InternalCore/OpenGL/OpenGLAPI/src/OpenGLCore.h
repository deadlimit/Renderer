#pragma once

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"

#define SHADER_RESOURCE(x) "../InternalCore/OpenGL/Resources/Shaders/"##x

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;

	static constexpr unsigned int Stride = sizeof(float) * 6;
};
