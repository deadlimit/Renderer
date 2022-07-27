#include "Renderer.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "OpenGL/Shader.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/Texture.h"
#include "OpenGL/Material.h"
#include "OpenGL/GameObject.h"
#include "OpenGL/Primitives.h"
#include "OpenGL/RenderViewport.h"

void Renderer::Init(GLFWwindow* window, ViewportSize viewportSize) {

	std::cout << "Initiating OpenGL" << std::endl;

	m_Window = window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glViewport(0, 0, viewportSize.width, viewportSize.height);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { Renderer::Get().ResizeViewport(width, height); });

	OpenGL::Shader wallShader(SHADER_RESOURCE("Triangle1.shader"));
	OpenGL::Texture wallTexture(TEXTURE_RESOURCE("wall.jpg"));
	OpenGL::Material material(wallShader, wallTexture);
	OpenGL::Mesh square(OpenGL::Square.vertices, OpenGL::Square.indicies, material);

	OpenGL::GameObject go(square);

	go.Bind();
	go.GetMaterial().GetShader().SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.f), 800.f / 600.0f, 0.01f, 100.f));
	go.GetMaterial().GetShader().SetUniformMatrix4fv("view", glm::translate(m_Camera.GetViewMatrix(), glm::vec3(0.0f, 0.0f, -2.0f)));
	go.GetMaterial().GetShader().SetUniformMatrix4fv("model", go.transform);

	m_RenderObjects.push_back(std::move(go));

	m_RenderViewport = new OpenGL::RenderViewport(viewportSize.width, viewportSize.height);
	
}

void Renderer::Run() {
	Draw();
}


void Renderer::Clear() {

	//Clear viewport
	SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	m_RenderViewport->Clear();

	//Clear window
	SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapFramebuffer() const {
	glfwSwapBuffers(m_Window);
}


void Renderer::ResizeViewport(int newWidth, int newHeight) {
	m_RenderViewport->Resize(newWidth, newHeight);
}

void Renderer::SetClearColor(glm::vec4 color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::Draw() {

	m_RenderViewport->Bind();

	for (int i = 0; i < m_RenderObjects.size(); ++i) {

		m_RenderObjects[i].Bind();

		m_RenderObjects[i].transform = glm::rotate(m_RenderObjects[i].transform, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("model", m_RenderObjects[i].transform);

		glm::mat4 camera = m_Camera.GetViewMatrix();

		camera = glm::rotate(camera, glm::radians((float)glm::sin(glfwGetTime()) * 10), glm::vec3(0, 1, 0));

		auto [width, height] = m_RenderViewport->GetSize();

		m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("view", glm::translate(camera, glm::vec3(0.0f, 0.0f, -3.0f)));
		m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("projection", glm::perspective(glm::radians(45.0f), (float)width/ (float)height, 0.01f, 100.f));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	m_RenderViewport->Unbind();

}



void Renderer::Clean() {



}
