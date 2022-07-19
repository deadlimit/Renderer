#pragma once
#include "glm.hpp"
#include "VulkanCore.h"
#include <array>

//float: VK_FORMAT_R32_SFLOAT
//vec2 : VK_FORMAT_R32G32_SFLOAT
//vec3 : VK_FORMAT_R32G32B32_SFLOAT
//vec4 : VK_FORMAT_R32G32B32A32_SFLOAT

struct Vertex {
	glm::vec2 Position;
	glm::vec3 Color;
	glm::vec2 UV;

	static VkVertexInputBindingDescription BindingDescription() {

		VkVertexInputBindingDescription description{};
		description.binding = 0;
		description.stride = sizeof Vertex;
		description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return description;
	}

	static std::array<VkVertexInputAttributeDescription, 3> AttributeDescription() {
		std::array< VkVertexInputAttributeDescription, 3> attributeDescription{};

		attributeDescription[0].binding = 0;
		attributeDescription[0].location = 0;
		attributeDescription[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescription[0].offset = offsetof(Vertex, Position);

		attributeDescription[1].binding = 0;
		attributeDescription[1].location = 1;
		attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescription[1].offset = offsetof(Vertex, Color);

		attributeDescription[2].binding = 0;
		attributeDescription[2].location = 2;
		attributeDescription[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescription[2].offset = offsetof(Vertex, UV);

		return attributeDescription;
	}
};

