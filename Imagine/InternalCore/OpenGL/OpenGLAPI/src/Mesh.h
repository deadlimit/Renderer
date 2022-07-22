#pragma once
#include <vector>
#include "Material.h"
#include "Shader.h"
#include "OpenGLCore.h"

namespace OpenGL {

	class Mesh {

	public:
		Mesh(const std::vector<Vertex>, const std::vector<unsigned int>&, const Material&);

		Mesh(const Mesh&);

		void Bind() const;

	private:

		Material m_Material;
		unsigned int m_VAO;

	};


}


