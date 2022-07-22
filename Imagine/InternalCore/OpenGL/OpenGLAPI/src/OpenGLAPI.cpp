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

		glViewport(0, 0, 800, 600);

		Shader wallShader(SHADER_RESOURCE("Triangle1.shader"));
		wallShader.Bind();
		Texture wallTexture(TEXTURE_RESOURCE("wall.jpg"));
		
	
		std::vector<unsigned int> indices = {
			0, 1, 2,
			2, 3, 0
		};

		Material material(wallShader, wallTexture);
		Mesh square(Square.vertices, Square.indicies, material);

		GameObject go(square);

		wallShader.SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.f), 800.f / 400.f, 0.1f, 100.f));
		wallShader.SetUniformMatrix4fv("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
		wallShader.SetUniformMatrix4fv("model", go.transform);

		m_RenderObjects.push_back(std::move(go));

	}

	void GraphicsAPI::Run() {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();

		DrawObjects();

		glfwSwapBuffers(m_Window);
	}

	void GraphicsAPI::DrawObjects() {

		for (int i = 0; i < m_RenderObjects.size(); ++i) {
			m_RenderObjects[i].Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}

	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}



}

