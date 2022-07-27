#include "Camera.h"
#include "gtc/matrix_transform.hpp"

namespace OpenGL {

	void Camera::Move(glm::vec3 direction) {
	
		glm::vec3 newPos = glm::vec3(m_ViewMatrix[1]) + direction;

		m_ViewMatrix = glm::translate(m_ViewMatrix, newPos);
			
	}

}


