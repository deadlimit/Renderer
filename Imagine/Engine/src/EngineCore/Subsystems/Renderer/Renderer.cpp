#include "Renderer.h"
#include "../../Subsystems/GUI/GUI.h"
#include <iostream>
#include <stdexcept>
#include "Utils/Utils.h"

static void OpenGLDebugCallback(GLenum source, GLenum type, GLuint ID, GLenum severity, GLsizei length, const GLchar* message, const void* userParams) {
	std::cout << message << std::endl;
}

void Renderer::Init(GLFWwindow* window, uint32_t viewportWidth, uint32_t viewportHeight) {

	GUI::PrintToConsole("Initiating OpenGL");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glViewport(0, 0, viewportWidth, viewportHeight);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {	
		Utils::g_InitParams.windowWidth = width;
		Utils::g_InitParams.windowHeight = height;
		Renderer::ResizeViewport(width, height);}
	);

	glDebugMessageCallback(OpenGLDebugCallback, nullptr);

	ResizeViewport(viewportWidth, viewportHeight);

}

void Renderer::Draw(std::unordered_map<uint32_t, Renderer::RenderInformation>& renderData, const uint32_t framebufferID) {

	if(framebufferID)
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	for (auto& it = renderData.cbegin(); it != renderData.end(); ++it) {
		glBindVertexArray(it->second.VAO);
		glUseProgram(it->second.shader.ProgramID);
		glBindTexture(GL_TEXTURE_2D, it->second.textureID);
		glDrawElements(GL_TRIANGLES, it->second.indicies, GL_UNSIGNED_INT, 0);

	}

	if (framebufferID)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Clear(const uint32_t framebufferID) {

	if (framebufferID) {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}


//TODO This runs on window resize, should compensate 
void Renderer::ResizeViewport(int newWidth, int newHeight) {

	static GLint ViewportSize[4];

	glGetIntegerv(GL_VIEWPORT, ViewportSize);

	if (ViewportSize[2] == newWidth && ViewportSize[3] == newHeight)
		return;

	glViewport(0, 0, newWidth, newHeight);

	//If a framebuffer exists it needs to be deleted in order to be recreated
	if (Framebuffer.ID) {

		glDeleteFramebuffers(1, &Framebuffer.ID);
		glDeleteTextures(1, &Framebuffer.ColorAttachment);

	}

	glGenFramebuffers(1, &Framebuffer.ID);
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer.ID);

	glCreateTextures(GL_TEXTURE_2D, 1, &Framebuffer.ColorAttachment);
	glBindTexture(GL_TEXTURE_2D, Framebuffer.ColorAttachment);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Framebuffer.ColorAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("Failed to recreate framebuffer");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}


void Renderer::SwapBuffers(GLFWwindow& window) {
	glfwSwapBuffers(&window);
}
