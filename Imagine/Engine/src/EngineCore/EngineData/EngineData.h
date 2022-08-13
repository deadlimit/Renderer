#pragma once
#include "glm.hpp"
#include "glad.h"
#include "glfw3.h"

namespace EngineData {

	struct Viewport {
		glm::vec2 Size;
		glm::vec4 Position;
	};

	struct EditorCameraData {
		glm::vec3 Position;
		glm::vec3 Forward;
		glm::vec3 Up;
		float Pitch;
		float Yaw;
		unsigned int ViewMode;
		glm::mat4 Projection;
		float FOV;
		float Clipping_Near;
		float Clipping_Far;
	};

	struct MainWindow {
		glm::vec2 Size;
		GLFWwindow* Handle;
	};

	inline Viewport g_ViewportData;
	inline EditorCameraData g_EditorCameraData;
	inline MainWindow g_MainWindow;

}


