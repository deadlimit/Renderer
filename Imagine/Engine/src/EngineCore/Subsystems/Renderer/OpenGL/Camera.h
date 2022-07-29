#pragma once
#include "OpenGLCore.h"

namespace Renderer {

	class Camera {

	public:

		Camera(glm::mat4 matrix) : m_ViewMatrix(matrix) {}

		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

		void Move(glm::vec3);

	private:

		glm::mat4 m_ViewMatrix;

	};
}



