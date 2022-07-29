#include "ResourceManager.h"

const std::string ResourceManager::LoadShader(const std::string& filename) {
	
	return "../Resources/Shaders/OpenGL/" + filename;

}

const std::string ResourceManager::LoadTexture(const std::string& filename) {
	return "../Resources/Textures/" + filename;
}
