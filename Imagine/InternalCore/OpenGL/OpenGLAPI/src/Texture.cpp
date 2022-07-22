#include "Texture.h"
#include "OpenGLCore.h"
#include "Image.h"

namespace OpenGL {
	
	Texture::Texture(const char* file) {

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

	}

	Texture::~Texture() {
		glDeleteTextures(1, &m_TextureID);
	}

	Texture::Texture(const Texture& other ) : m_TextureID(other.m_TextureID) {}

	void Texture::Bind() const {
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

}


