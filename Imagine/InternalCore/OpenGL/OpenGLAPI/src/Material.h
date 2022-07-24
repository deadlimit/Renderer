#pragma once

#include "Shader.h"
#include "Texture.h"

namespace OpenGL{

	class Material {

	public:
		Material() {}
		Material(Shader&, Texture&);
		Material(Material&&);
		~Material();

		Shader& GetShader() { return m_Shader; }

		void Bind() const;

	private:

		Shader m_Shader;
		Texture m_Texture;

	};

}



