#include "OpenGLAPI.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Shader.h"

namespace OpenGL {

	void GraphicsAPI::Init() {
		std::cout << "Initiating OpenGL" << std::endl;

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(800, 400, "OpenGL", nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to init GLAD");
			return;
		}
	}

	void GraphicsAPI::Run() {

		glViewport(0, 0, 800, 400);

		Shader shader(SHADER_RESOURCE("Triangle.shader"));

		/*
		std::vector<Vertex> vertices = {
			{{-0.5f, -0.5f, 0.0f}},
			{{0.0f,  0.5f, 0.0f}},
			{{ 0.5f, -0.5f, 0.0f}},
		};
		*/

		float vertices[] = {
			-0.5f, -0.5f, 1.0f,
			0.0f,  0.5f, 1.0f,
			0.5f, -0.5f, 1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2
		};


		GLuint VAO;
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		GLuint VBO;
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

	
		while (!glfwWindowShouldClose(m_Window)) {


			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();


			glBindVertexArray(VAO);
			shader.Bind();
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


			glfwSwapBuffers(m_Window);
		}

	}

	void GraphicsAPI::CreateTriangleTest() {





	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}

}

