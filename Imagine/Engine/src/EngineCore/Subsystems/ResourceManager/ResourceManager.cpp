#include "ResourceManager.h"
#include "Subsystems/Renderer/OpenGL/stb_image.h"

const std::string ResourceManager::LoadShader(const std::string& filename) {
	
	return "../Resources/Shaders/OpenGL/" + filename;

}

const std::string ResourceManager::LoadTexture(const std::string& filename) {
	return "../Resources/Textures/" + filename;
}

void ResourceManager::LoadObj(const std::string& fíle) {


}
