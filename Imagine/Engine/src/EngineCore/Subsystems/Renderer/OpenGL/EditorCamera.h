#pragma once
#include "OpenGLCore.h"

namespace Renderer {

	class EditorCamera {

	public:

		EditorCamera(glm::mat4 matrix);

		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

		void Move(const glm::vec3&);
		void Rotate(const glm::vec3&);

	private:

		glm::mat4 m_ViewMatrix;

	};
}



