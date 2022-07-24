#include "Material.h"
#include <iostream>

namespace OpenGL {

	Material::Material(Shader& shader, Texture& texture) : m_Shader(std::move(shader)), m_Texture(std::move(texture)) {}

	Material::Material(Material&& other ) : m_Shader(std::move(other.m_Shader)), m_Texture(std::move(other.m_Texture)) {
		std::cout << "Move constructor for Material" << std::endl;
	}

	Material::~Material() {
	}

	void Material::Bind() const {
		m_Texture.Bind();
		m_Shader.Bind();
	}

}


