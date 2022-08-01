#include "InputManager.h"
#include "Engine.h"
#include <iostream>

namespace InputManager {

	void HandleInput() {

		glm::vec3 direction(0.0f);
		glm::vec3 rotation(0.0f);

		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_W)) {
			direction.z += 0.01f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_S)) {
			direction.z -= 0.01f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_A)) {
			direction.x += 0.01f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_D)) {
			direction.x -= 0.01f;
		}		
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_E)) {
			direction.y -= 0.01f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_Q)) {
			direction.y += 0.01f;
		}


		if (direction.length() > 0.0f) 
			Engine::EditorCamera.Move(direction);
		
	//	if (rotation.length() > 0.0f)
		//	Engine::EditorCamera.Rotate(rotation);

	}
}

