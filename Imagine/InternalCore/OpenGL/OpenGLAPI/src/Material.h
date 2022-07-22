#pragma once

#include "Shader.h"
#include "Texture.h"

namespace OpenGL{

	class Material {

	public:
		Material() {}
		Material(const Shader&, Texture&);
		Material(Material&&);
		~Material();


		void Bind() const;

	private:

		Shader m_Shader;
		Texture m_Texture;

	};

}



