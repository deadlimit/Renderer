#include "GameObject.h"

OpenGL::GameObject::GameObject(Mesh& mesh) : m_Mesh(mesh), transform(glm::mat4(1.0f)) {}

void OpenGL::GameObject::Draw() const {
	m_Mesh.Bind();
}
