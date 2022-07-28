#pragma once

namespace OpenGL {

	class Texture {
		
	public:
		Texture() {}
		Texture(const char*);
		~Texture();
		Texture(Texture&&);
		Texture(const Texture&);

		void Bind() const;

	private:

		unsigned int m_TextureID;

	};



}

