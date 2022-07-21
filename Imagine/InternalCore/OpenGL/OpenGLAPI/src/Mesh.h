#pragma once
#include <vector>

#include "Shader.h"
#include "OpenGLCore.h"

namespace OpenGL {

	class Mesh {

	public:
		Mesh(const std::vector<Vertex>, const std::vector<unsigned int>&, Shader&);

		void Bind() const;

	private:

		Shader& m_Shader;

		unsigned int m_VAO;

	};


}


