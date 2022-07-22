#pragma once
#include <vector>
#include "Material.h"
#include "Shader.h"
#include "OpenGLCore.h"

namespace OpenGL {

	class Mesh {

	public:
		Mesh() {}
		Mesh(const std::vector<Vertex>, const std::vector<unsigned int>&, Material&);
		Mesh(Mesh&&) noexcept;

		const Material& GetMaterial() const { return m_Material; }
		const unsigned int GetID() const { return m_VAO; }

		void Bind() const;

	private:

		Material m_Material;
		unsigned int m_VAO;

	};


}


