#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include "Engine.h"
#include <iostream>
#include "glfw3.h"

namespace EditorCamera {

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Up;

	float pitch = 0;
	float yaw = -90.f;
	float roll = 0;

	static float Speed = .005f;

	void Init(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, const bool& activate) {
		Position = position;
		Forward = forward;
		Up = up;
		Activate(activate);
	}

	static double previousXPosition;
	static double previousYPosition;
	static float mouse_sensitivity = 0.1f;

	static void Rotate(GLFWwindow* window, double xPos, double yPos) {

		double deltaX = xPos - previousXPosition;
		double deltaY = previousYPosition - yPos;

		previousXPosition = xPos;
		previousYPosition = yPos;

		deltaX *= mouse_sensitivity;
		deltaY *= mouse_sensitivity;

		yaw += deltaX;
		pitch += deltaY;

		pitch = glm::clamp(pitch, -90.f, 90.f);

		glm::vec3 direction;

		direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
		direction.y = glm::sin(glm::radians(pitch));
		direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

		Forward = glm::normalize(direction);
	}

	void Activate(const bool& activate) {

		glfwSetCursorPosCallback(Engine::MainWindow, (activate ? Rotate : nullptr));

	}

	void EditorCamera::Move(const glm::vec3& direction) {

		if (glm::abs(direction.z))
			Position += Forward * direction.z * Speed;

		if (glm::abs(direction.y))
			Position += Up * direction.y * Speed;

		if(glm::abs(direction.x))
			Position += glm::normalize(glm::cross(Forward, Up) * direction.x) * Speed;
		
	}

	glm::mat4 GetViewMatrix() {

		return glm::lookAt(Position, Position + Forward, Up);
	}


}





