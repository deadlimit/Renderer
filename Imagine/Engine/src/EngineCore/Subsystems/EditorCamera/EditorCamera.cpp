#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include "Engine.h"
#include <iostream>
#include "glfw3.h"


namespace EditorCamera {

#define VECTOR_FORWARD glm::vec3( 0, 0, 1)
#define VECTOR_BACK	   glm::vec3( 0, 0,-1)
#define VECTOR_RIGHT   glm::vec3( 1, 0, 0)
#define VECTOR_LEFT	   glm::vec3(-1, 0, 1)
#define VECTOR_UP	   glm::vec3( 0, 1, 0)
#define VECTOR_DOWN	   glm::vec3( 0,-1, 0)

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

		InputManager::RegisterCallback(GLFW_KEY_W, []() { Move(VECTOR_FORWARD); });
		InputManager::RegisterCallback(GLFW_KEY_S, []() { Move(VECTOR_BACK);	});
		InputManager::RegisterCallback(GLFW_KEY_A, []() { Move(VECTOR_LEFT);	});
		InputManager::RegisterCallback(GLFW_KEY_D, []() { Move(VECTOR_RIGHT);	});
		InputManager::RegisterCallback(GLFW_KEY_E, []() { Move(VECTOR_UP);		});
		InputManager::RegisterCallback(GLFW_KEY_Q, []() { Move(VECTOR_DOWN);	});

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

	
	void Activate() {
		glfwSetCursorPosCallback(Engine::MainWindow, Rotate);
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





