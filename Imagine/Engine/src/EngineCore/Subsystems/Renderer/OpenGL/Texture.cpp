#include "Texture.h"
#include "Image.h"
#include <iostream>
#include "Subsystems/ResourceManager/ResourceManager.h"

namespace Renderer {
	
	 void CreateTexture(const std::string& filepath, uint32_t& textureID) {

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		std::string fullPath = ResourceManager::LoadTexture(filepath);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}


	void DeleteTexture(uint32_t& textureID) {
		glDeleteTextures(1, &textureID);
	}

}


