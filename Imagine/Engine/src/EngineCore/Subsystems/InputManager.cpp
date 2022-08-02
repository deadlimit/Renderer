#include "InputManager.h"
#include "Subsystems/EditorCamera/EditorCamera.h"
#include "Engine.h"
#include <iostream>

namespace InputManager {

	void HandleInput() {

		glm::vec3 direction(0.0f);
		glm::vec3 rotation(0.0f);

		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_W)) {
			direction.z += 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_S)) {
			direction.z -= 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_A)) {
			direction.x -= 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_D)) {
			direction.x += 1.f;
		}		
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_E)) {
			direction.y += 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_Q)) {
			direction.y -= 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_UP)) {
			rotation.x = 1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_DOWN)) {
			rotation.x = -1.f;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_LEFT)) {
			rotation.y = 1.f;;
		}
		if (glfwGetKey(Engine::MainWindow, GLFW_KEY_RIGHT)) {
			rotation.y = 1.f;
		}


		if (glm::sqrt(glm::pow(direction.x, 2) + glm::pow(direction.y, 2) + glm::pow(direction.z, 2)) > 0.0f) {
			EditorCamera::Move(direction);
		}
		
		if (glm::sqrt(glm::pow(rotation.x, 2) + glm::pow(rotation.y, 2) + glm::pow(rotation.z, 2)) > 0.0f) {
			
			EditorCamera::Rotate(rotation);
		}

	}
}

