#pragma once
#include "Utils/Math.h"
#include "glad.h"
#include "glfw3.h"

namespace EngineData {

	struct Viewport {
		Vector2 Size;
		Vector4 Position;
	};

	struct EditorCamera {
		Vector3 Position;
		Vector3 Forward;
		Vector3 Up;
		float Pitch;
		float Yaw;
		unsigned int ViewMode;
	};

	struct MainWindow {
		Vector2 Size;
		GLFWwindow* Handle;
	};

	inline Viewport g_ViewportData;
	inline EditorCamera g_EditorCameraData;
	inline MainWindow g_MainWindow;

}


