#pragma once
#include "OpenGLCore.h"

namespace Renderer {

	class EditorCamera {

	public:

		EditorCamera(glm::mat4 matrix);

		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }

	private:

		glm::mat4 m_ViewMatrix;

	};
}



