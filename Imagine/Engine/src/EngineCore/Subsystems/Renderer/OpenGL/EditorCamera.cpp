#include "EditorCamera.h"
#include "gtc/matrix_transform.hpp"
#include "Subsystems/InputManager.h"
#include <iostream>
namespace Renderer {

	EditorCamera::EditorCamera(glm::mat4 matrix) : m_ViewMatrix(matrix) {}

	void EditorCamera::Move(const glm::vec3& direction) {
		
		m_ViewMatrix = glm::translate(m_ViewMatrix, direction);

	}

	void EditorCamera::Rotate(const glm::vec3& rotation) {

		m_ViewMatrix = glm::rotate(m_ViewMatrix, glm::radians(0.1f), rotation);

	}

}


