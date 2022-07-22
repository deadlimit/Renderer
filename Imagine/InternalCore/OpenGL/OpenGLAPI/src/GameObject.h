#pragma once

#include "Mesh.h"

namespace OpenGL {
	class GameObject {

	public:
		GameObject(Mesh&);

		void Draw() const;

		glm::mat4 transform;

	private:

		Mesh m_Mesh;

	};
}



