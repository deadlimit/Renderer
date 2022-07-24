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


	GraphicsAPI::GraphicsAPI() : m_Camera(glm::mat4(1.0f)) {}

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
		Texture wallTexture(TEXTURE_RESOURCE("wall.jpg"));
		Material material(wallShader, wallTexture);
		Mesh square(Square.vertices, Square.indicies, material);

		GameObject go(square);

		go.Bind();
		
		
		
		go.GetMaterial().GetShader().SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.f), 800.f / 600.0f, 0.01f, 100.f));
		go.GetMaterial().GetShader().SetUniformMatrix4fv("view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -2.0f)));
		go.GetMaterial().GetShader().SetUniformMatrix4fv("model", go.transform);

		m_RenderObjects.push_back(std::move(go));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	}

	void GraphicsAPI::Run() {

		
		glfwPollEvents();

		DrawObjects();

		glfwSwapBuffers(m_Window);

	}

	void GraphicsAPI::Clear() {

		
		glClear(GL_COLOR_BUFFER_BIT);
		
	}
	
	void GraphicsAPI::DrawObjects() {

		glViewport(0, 0, 800, 600);

		for (int i = 0; i < m_RenderObjects.size(); ++i) {
	
			m_RenderObjects[i].Bind();

			m_RenderObjects[i].transform = glm::rotate(m_RenderObjects[i].transform, glm::radians(0.03f), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("model", m_RenderObjects[i].transform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}		

	}

	void GraphicsAPI::Clean() {

		glfwDestroyWindow(m_Window);

		glfwTerminate();

	}



}

