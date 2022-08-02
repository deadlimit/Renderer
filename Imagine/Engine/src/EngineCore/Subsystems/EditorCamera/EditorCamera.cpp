#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include <iostream>

namespace EditorCamera {

	static glm::vec3 Position;
	static glm::vec3 Forward;
	static glm::vec3 Up;

	void Init(const glm::vec3& position, const glm::vec3& forward, const glm::vec3& up) {
		Position = position;
		Forward = forward;
		Up = up;
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Forward, Up);
	}

	void EditorCamera::Move(const glm::vec3& direction) {
		Position += direction;
	}

	void EditorCamera::Rotate(const glm::vec3& rotation) {

		//m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(0.1f), rotation);

	}
}





