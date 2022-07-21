#include "OpenGLAPI.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

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

		Shader shader1(SHADER_RESOURCE("Triangle1.shader"));
		Shader shader2(SHADER_RESOURCE("Triangle2.shader"));

		std::vector<Vertex> vertices1 = {
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
			{{ -0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
			{{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}
		};

		
		std::vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		
		Texture texture(TEXTURE_RESOURCE("wall.jpg"));

		Mesh triangle1(vertices1, indices, shader1);
		
		while (!glfwWindowShouldClose(m_Window)) {

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();

			triangle1.Bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			
			glfwSwapBuffers(m_Window);
		}

	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}

}

