#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include <iostream>
#include "Subsystems/GUI/GUI.h"

namespace EditorCamera {

	static glm::vec3 Position;
	static glm::vec3 Forward;
	static glm::vec3 Up;

	static float pitch = 0;
	static float yaw = -90.f;
	static float roll = 0;


	static float Speed = .01f;

	void Init(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up) {
		Position = position;
		Forward = forward;
		Up = up;
	}


	void EditorCamera::Move(const glm::vec3& direction) {

		if (glm::abs(direction.z))
			Position += Forward * direction.z * Speed;

		if (glm::abs(direction.y))
			Position += Up * direction.y * Speed;

		if(glm::abs(direction.x))
			Position += glm::normalize(glm::cross(Forward, Up) * direction.x) * Speed;
		
	}

	void EditorCamera::Rotate(const glm::vec3& rotation) {

		pitch = glm::cos(glm::radians(rotation.x));
		yaw = glm::sin(glm::radians(rotation.x));
	}

	glm::mat4 GetViewMatrix() {
		GUI::PrintToConsole(std::to_string(Position.x));

		return glm::lookAt(Position, Position + Forward, Up);
	}


}





