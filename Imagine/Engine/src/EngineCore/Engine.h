#pragma once

#include "Subsystems/Renderer/Renderer.h"
#include "glad.h"
#include "glfw3.h"
#include <map>

namespace Engine {
	void Init();
	void Run();
	void Clean();

	inline GLFWwindow* MainWindow = nullptr;

	inline Renderer::EditorCamera EditorCamera(glm::mat4(1.0f));
}




