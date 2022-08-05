#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include "Engine.h"
#include <iostream>
#include "glfw3.h"
#include "../Utils.h"

#define VECTOR_FORWARD glm::vec3( 0, 0, 1)
#define VECTOR_BACK	   glm::vec3( 0, 0,-1)
#define VECTOR_RIGHT   glm::vec3( 1, 0, 0)
#define VECTOR_LEFT	   glm::vec3(-1, 0, 0)
#define VECTOR_UP	   glm::vec3( 0, 1, 0)
#define VECTOR_DOWN	   glm::vec3( 0,-1, 0)

namespace EditorCamera {

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Up;

	static float Speed = .0005f;

	void Init(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up, const bool& activate) {
		Position = position;
		Forward = forward;
		Up = up;


		//Need to find a way to skip repeating things
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_W, { nullptr, []() { Move(VECTOR_FORWARD);}, nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_S, { nullptr, []() { Move(VECTOR_BACK);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_A, { nullptr, []() { Move(VECTOR_LEFT);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_D, { nullptr, []() { Move(VECTOR_RIGHT);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_E, { nullptr, []() { Move(VECTOR_UP);},		 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_Q, { nullptr, []() { Move(VECTOR_DOWN);},	 nullptr });

		InputManager::RegisterCallback(InputType::MOUSE, GLFW_MOUSE_BUTTON_2,
			{
			[]() { //glfwSetInputMode(Engine::MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				   glfwSetCursorPos(Engine::MainWindow, Utils::g_InitParams.viewportWidth / 2, Utils::g_InitParams.viewportHeight / 2); },
			[]() { Rotate(); }, 
			[]() { glfwSetInputMode(Engine::MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
			});
	}

	static double previousXPosition = 0.0f;
	static double previousYPosition = -90.f;
	static float mouse_sensitivity = 0.1f;

	void Rotate() {

		double xPos, yPos;
		glfwGetCursorPos(Engine::MainWindow, &xPos, &yPos);
	
		double deltaX = xPos - previousXPosition;
		double deltaY = previousYPosition - yPos;

		if (deltaX == 0 && deltaY == 0)
			return;
		
		std::cout << deltaX << " " << deltaY << std::endl;
		
		previousXPosition = xPos;
		previousYPosition = yPos;

		deltaX *= mouse_sensitivity;
		deltaY *= mouse_sensitivity;

		Rotation.y += deltaX;
		Rotation.x += deltaY;

		Rotation.x = glm::clamp(Rotation.x, -90.f, 90.f);

		glm::vec3 direction;

		direction.x = glm::cos(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));
		direction.y = glm::sin(glm::radians(Rotation.x));
		direction.z = glm::sin(glm::radians(Rotation.y)) * glm::cos(glm::radians(Rotation.x));

		Forward = glm::normalize(direction);
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





