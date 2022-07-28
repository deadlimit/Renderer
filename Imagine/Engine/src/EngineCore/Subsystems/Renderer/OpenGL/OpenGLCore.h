#pragma once

#include "glad.h"
#include "glfw3.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#define SHADER_RESOURCE(x) "../InternalCore/OpenGL/Resources/Shaders/"##x
#define TEXTURE_RESOURCE(x) "../InternalCore/OpenGL/Resources/Textures/"##x

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 UV;

	static constexpr unsigned int Stride = sizeof(float) * 8;
};
