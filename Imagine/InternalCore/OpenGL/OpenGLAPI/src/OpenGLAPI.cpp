#include "OpenGLAPI.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "GameObject.h"
#include "Primitives.h"
#include "glm.hpp""
#include "gtc/matrix_transform.hpp"


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

		Shader wallShader(SHADER_RESOURCE("Triangle1.shader"));
		Texture wallTexture(TEXTURE_RESOURCE("wall.jpg"));

		std::vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		Material material(wallShader, wallTexture);
		Mesh square(Square.vertices, Square.indicies, material);
	
		GameObject go(square);

		
		wallShader.Bind();

		while (!glfwWindowShouldClose(m_Window)) {

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();

			go.Draw();

			go.transform = glm::translate(go.transform, glm::vec3(-0.0001f, 0.0f, 0.0f));
			go.transform = glm::rotate(go.transform, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
			go.transform = glm::scale(go.transform, glm::vec3(1.0f, 1.0f, 1.0f));

			wallShader.SetUniformMatrix4fv("u_Transform", go.transform);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			
			glfwSwapBuffers(m_Window);
		}

	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}

}

