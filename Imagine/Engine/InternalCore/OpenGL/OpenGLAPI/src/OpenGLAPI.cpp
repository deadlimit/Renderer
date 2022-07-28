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

	GraphicsAPI::GraphicsAPI() : m_Camera(glm::mat4(1.0f)), m_Framebuffer(nullptr) {}

	void GraphicsAPI::Init(GLFWwindow* window, uint32_t width, uint32_t height) {
		
	
		

		m_Window = window;

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

		glViewport(0, 0, width, height);

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

		m_Framebuffer = new Framebuffer(width, height);
	}

	void GraphicsAPI::Run() {

		
		DrawObjects();

	}

	void GraphicsAPI::Clear() {
		glfwSwapBuffers(m_Window);
		glClear(GL_COLOR_BUFFER_BIT | GL_COLOR_ATTACHMENT0);		
	}
	
	void GraphicsAPI::DrawObjects() {

		m_Framebuffer->Bind(true);

		for (int i = 0; i < m_RenderObjects.size(); ++i) {
	
			m_RenderObjects[i].Bind();

			m_RenderObjects[i].transform = glm::rotate(m_RenderObjects[i].transform, glm::radians(0.03f), glm::vec3(0.0f, 0.0f, 1.0f));
			m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("model", m_RenderObjects[i].transform);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}		

		m_Framebuffer->Bind(false);
	}

	void GraphicsAPI::Clean() {}


}

