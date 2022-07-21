#include "Material.h"

namespace OpenGL {

	Material::Material(const Shader& shader, Texture& texture) : m_Shader(shader), m_Texture(texture) {}

}


