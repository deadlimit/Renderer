#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include "glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw3native.h"
#include <optional>
#include <stdexcept>
#include "glm.hpp"
#include "Vertex.h"
#include <vector>

namespace Vulkan {

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif


	struct MeshData {

		std::vector<Vertex> Vertices;
		std::vector<uint16_t> Indices;

		VkDeviceSize Size() const { return sizeof Vertex * Vertices.size(); }
	};


	struct QueueFamilies {
		std::optional<uint32_t> graphics;
		std::optional<uint32_t> compute;
		std::optional<uint32_t> transfer;
		std::optional<uint32_t> sparse;
		std::optional<uint32_t> presentation;
	};

	struct UniformBufferObject {
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 proj;
	};

#define VKCALL(x) if(x != VK_SUCCESS) throw std::runtime_error(__FILE__ + __LINE__)

}