#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include "Engine.h"
#include <iostream>
#include "glfw3.h"
#include "EngineData/EngineData.h"
#include "imgui.h"

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

	static float Speed = 0.005f;
	static double previousXPosition;
	static double previousYPosition;

	static void CenterAndHideMouseCursor() {

		int centerX = EngineData::g_Data.ViewportWindowPosition.x + (EngineData::g_Data.ViewportSize.x * .5f); 
		int centerY = EngineData::g_Data.ViewportWindowPosition.y + (EngineData::g_Data.ViewportSize.y * .5f);

		double xPosition, yPosition;
		glfwGetCursorPos(Engine::MainWindow, &xPosition, &yPosition);

		previousXPosition = xPosition;
		previousYPosition = yPosition;

		glfwSetInputMode(Engine::MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		
	}


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
			[]() { CenterAndHideMouseCursor(); },
			[]() { Rotate(); },
			[]() { glfwSetInputMode(Engine::MainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
			});
	}


	static float mouse_sensitivity = 0.2f;

	void Rotate() {
		
		double xPosition, yPosition;
		glfwGetCursorPos(Engine::MainWindow, &xPosition, &yPosition);

		float deltaX = xPosition - previousXPosition;
		float deltaY = previousYPosition - yPosition;

		previousXPosition = xPosition;
		previousYPosition = yPosition;

		//float length = glm::sqrt(glm::pow(deltaX, 2) + glm::pow(deltaY, 2));

		//Normalize
		//deltaX /= length;
	//	deltaY /= length;

		pitch += (deltaY * mouse_sensitivity);
		yaw += (deltaX * mouse_sensitivity);

		if (pitch > 89.f)
			pitch = 89.f;
		if (pitch < -89.f)
			pitch = -89.f;
		if (yaw > 360.f)
			yaw -= 360.f;
		if(yaw < -360.f)
			yaw += 360.f;

		
		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(yaw));
		direction.y = glm::sin(glm::radians(pitch));
		direction.z = glm::sin(glm::radians(yaw) * glm::cos(glm::radians(pitch)));

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





