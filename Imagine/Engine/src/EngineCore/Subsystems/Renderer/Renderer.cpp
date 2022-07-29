#include "Renderer.h"
#include "../../Subsystems/GUI/GUI.h"
#include <iostream>
#include <stdexcept>

static void OpenGLDebugCallback(GLenum source, GLenum type, GLuint ID, GLenum severity, GLsizei length, const GLchar* message, const void* userParams) {
	std::cout << message << std::endl;
}

void Renderer::Init(GLFWwindow* window, ViewportSize viewportSize) {
		
	GUI::PrintToConsole("Initiating OpenGL");

	m_Window = window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glViewport(0, 0, viewportSize.width, viewportSize.height);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { Renderer::Get().ResizeViewport(width, height); });

	m_RenderViewport = new OpenGL::RenderViewport(viewportSize.width, viewportSize.height);
	
	glDebugMessageCallback(OpenGLDebugCallback, nullptr);

}

void Renderer::Draw(RenderInformation& renderInformation) {

	glBindVertexArray(renderInformation.VAO);
	renderInformation.p_Shader->Bind();
	glBindTexture(GL_TEXTURE_2D, renderInformation.textureID);
	glDrawElements(GL_TRIANGLES, renderInformation.indicies, GL_UNSIGNED_INT, 0);
}


void Renderer::Clear() {

	//Clear viewport
	m_RenderViewport->Clear();

	//Clear window
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapFramebuffer() const {
	glfwSwapBuffers(m_Window);
}


void Renderer::ResizeViewport(int newWidth, int newHeight) {
	m_RenderViewport->Resize(newWidth, newHeight);
}

void Renderer::Clean() {}


/* This is game logic, should not be in renderer
* 		m_RenderObjects[i].transform = glm::rotate(m_RenderObjects[i].transform, glm::radians(0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("model", m_RenderObjects[i].transform);

		glm::mat4 camera = m_Camera.GetViewMatrix();

		camera = glm::rotate(camera, glm::radians((float)glm::sin(glfwGetTime()) * 10), glm::vec3(0, 1, 0));

		auto [width, height] = m_RenderViewport->GetSize();

		m_RenderObjects[i].GetMaterial().GetShader().SetUniformMatrix4fv("view", glm::translate(camera, glm::vec3(0.0f, 0.0f, -3.0f)));
		*/

