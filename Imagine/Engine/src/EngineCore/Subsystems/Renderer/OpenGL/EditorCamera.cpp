#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include <iostream>
namespace Renderer {

	EditorCamera::EditorCamera(glm::mat4 matrix) : m_ViewMatrix(matrix) {
	
		InputManager::RegisterKeyCallback([](GLFWwindow* window, int key, int scancode, int actions, int mods) {

			if (key == GLFW_KEY_E && actions == GLFW_PRESS)
				std::cout << "E from camera" << std::endl;
			
		});

	}

}


