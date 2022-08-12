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

	static float Speed = 0.005f;
	static double previousXPosition;
	static double previousYPosition;

	static void CenterAndHideMouseCursor() {

		int centerX = EngineData::g_ViewportData.Size.x + (EngineData::g_ViewportData.Size.x * .5f);
		int centerY = EngineData::g_ViewportData.Size.y + (EngineData::g_ViewportData.Size.y * .5f);

		double xPosition, yPosition;
		glfwGetCursorPos(Engine::MainWindow, &xPosition, &yPosition);

		previousXPosition = xPosition;
		previousYPosition = yPosition;

		glfwSetInputMode(Engine::MainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		
	}

	void ResetPosition() {
		Position = { 0.0f, 0.0f, -3.0f };
		Forward = { 0.0f, 0.0f, -1.0f };
		Up = { 0.0f, 1.0f, 0.0f };
		Pitch = 0;
		Yaw = 0;
	}
	
	//Passing a variable that exist in the same struct that is used to pull transformation from is wierd, fix plz
	void Init(const EngineData::EditorCamera& data) {

		Position = { data.Position.x,  data.Position.y,  data.Position.z };
		Forward = { data.Forward.x, data.Forward.y, data.Forward.z };
		Up = { data.Up.x, data.Up.y, data.Up.z };

		switch ((ViewMode)data.ViewMode) {
			case ViewMode::Mode_2D:
				Pitch = 0.0f;
				Yaw = 0.0f;
				break;
			case ViewMode::Mode_3D:
				Pitch = data.Pitch;
				Yaw = data.Yaw;
		}

		Mode = (ViewMode)data.ViewMode;
		
		//Need to find a way to skip repeating things
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_W, { nullptr, []() { Move(VECTOR_FORWARD);}, nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_S, { nullptr, []() { Move(VECTOR_BACK);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_A, { nullptr, []() { Move(VECTOR_LEFT);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_D, { nullptr, []() { Move(VECTOR_RIGHT);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_E, { nullptr, []() { Move(VECTOR_UP);},		 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_Q, { nullptr, []() { Move(VECTOR_DOWN);},	 nullptr });
		InputManager::RegisterCallback(InputType::KEY, GLFW_KEY_F, { nullptr, []() { ResetPosition();},	 nullptr });
	}


	static float mouse_sensitivity = 0.2f;

	void Rotate() {
		
		double xPosition, yPosition;
		glfwGetCursorPos(Engine::MainWindow, &xPosition, &yPosition);

		float deltaX = xPosition - previousXPosition;
		float deltaY = previousYPosition - yPosition;

		previousXPosition = xPosition;
		previousYPosition = yPosition;

		Pitch += (deltaY * mouse_sensitivity);
		Yaw += (deltaX * mouse_sensitivity);

		if (Pitch > 89.f)
			Pitch = 89.f;
		if (Pitch < -89.f)
			Pitch = -89.f;
		if (Yaw > 360.f)
			Yaw -= 360.f;
		if(Yaw < -360.f)
			Yaw += 360.f;

		glm::vec3 direction;
		direction.x = glm::cos(glm::radians(Yaw) * glm::cos(glm::radians(Pitch)));
		direction.y = glm::sin(glm::radians(Pitch));
		direction.z = glm::sin(glm::radians(Yaw) * glm::cos(glm::radians(Pitch)));
			
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





