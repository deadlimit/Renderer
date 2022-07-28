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

		unsigned int GetID() const { return m_TextureID; }

	private:

		unsigned int m_TextureID;

	};



}

