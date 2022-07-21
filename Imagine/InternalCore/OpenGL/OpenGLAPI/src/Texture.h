#pragma once

namespace OpenGL {

	class Texture {
		
	public:
		Texture(const char*);
		~Texture();

		Texture(const Texture&);

	private:

		unsigned int m_TextureID;

	};



}

