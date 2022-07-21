#include "Mesh.h"
#include <iostream>

namespace OpenGL {

	Mesh::Mesh(const std::vector<Vertex> vertices, const std::vector<unsigned int>& indices, Shader& shader) : m_Shader(shader) {

		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * Vertex::Stride, vertices.data(), GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex::Stride, (void*)0);
		glEnableVertexAttribArray(0);

	}

	void Mesh::Bind() const {

		m_Shader.Bind();
		glBindVertexArray(m_VAO);

	}


}
