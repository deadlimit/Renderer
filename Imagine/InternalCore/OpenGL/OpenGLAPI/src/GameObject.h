#pragma once

#include "Mesh.h"
#include <iostream>

namespace OpenGL {
	class GameObject {

	public:
		GameObject(Mesh&);
		GameObject(Mesh&&);

		GameObject(GameObject&&) noexcept;

		void Bind() const;

		glm::mat4 transform;

	private:

		Mesh m_Mesh;

	};
}



