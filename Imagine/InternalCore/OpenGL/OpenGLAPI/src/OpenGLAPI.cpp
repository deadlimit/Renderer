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
#include "Camera.h"


namespace OpenGL {

	void GraphicsAPI::Init() {
		std::cout << "Initiating OpenGL" << std::endl;
		

		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to init GLAD");
			return;
		}
	}

	void GraphicsAPI::Run() {

		glViewport(0, 0, 800, 600);
		
		Shader wallShader(SHADER_RESOURCE("Triangle1.shader"));
		Texture wallTexture(TEXTURE_RESOURCE("wall.jpg"));

		std::vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		Material material(wallShader, wallTexture);
		Mesh square(Square.vertices, Square.indicies, material);
	
		GameObject go(square);

		Camera camera(glm::mat4(1.0f));
		
		wallShader.Bind();

		
		go.transform = glm::scale(go.transform, glm::vec3(1.0f, 1.0f, 1.0f));

		float x = -1.0f;

		while (!glfwWindowShouldClose(m_Window)) {

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwPollEvents();

			go.Draw();

			go.transform = glm::rotate(go.transform, glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 0.0f));

			wallShader.SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.0f), 800.0f / 400.0f, 0.1f, 100.0f));
			wallShader.SetUniformMatrix4fv("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, x)));
			wallShader.SetUniformMatrix4fv("model", go.transform);

			x -= 0.00005f;

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			
			glfwSwapBuffers(m_Window);
		}

	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}

}

