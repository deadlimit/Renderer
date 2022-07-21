#pragma once

#include "Shader.h"
#include "Texture.h"

namespace OpenGL{

	class Material {

	public:
		Material(const Shader&, Texture&);
		~Material();

	private:

		Shader m_Shader;
		Texture m_Texture;

	};

}



