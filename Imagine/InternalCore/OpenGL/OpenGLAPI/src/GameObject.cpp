#include "GameObject.h"

namespace OpenGL {

	GameObject::GameObject(Mesh& mesh) : m_Mesh(std::move(mesh)), transform(glm::mat4(1.0f)) {}

	GameObject::GameObject(Mesh&& mesh) : m_Mesh(std::move(mesh)), transform(glm::mat4(1.0f)) {}

	GameObject::GameObject(GameObject&& other) noexcept : m_Mesh(std::move(other.m_Mesh)), transform(glm::mat4(1.0f)) {
		std::cout << "Game object Moving" << std::endl;
	}


	void GameObject::Bind() const {
		m_Mesh.Bind();
	}


}

