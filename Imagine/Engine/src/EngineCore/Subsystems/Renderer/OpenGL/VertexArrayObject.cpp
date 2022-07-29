#include "VertexArrayObject.h"
#include <iostream>

namespace OpenGL {

		void CreateVertexArrayObject(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, uint32_t& VAO) {

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

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

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, Vertex::Stride, (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, Vertex::Stride, (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

	}
	void DeleteVertexArrayObject(uint32_t& VAO) {
		glDeleteVertexArrays(1, &VAO);
	}
}
