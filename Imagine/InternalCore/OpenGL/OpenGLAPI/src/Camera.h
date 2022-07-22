#pragma once
#include "OpenGLCore.h"

namespace OpenGL {

	class Camera {

	public:

		Camera(glm::mat4 matrix) : m_ViewMatrix(matrix) {}

		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	private:

		glm::mat4 m_ViewMatrix;

	};
}



