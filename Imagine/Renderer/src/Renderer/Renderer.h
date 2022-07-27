#pragma once

#include "../System.h"
#include "OpenGL/OpenGLCore.h"
#include "OpenGL/GameObject.h"
#include "OpenGL/Camera.h"
#include "OpenGL/Framebuffer.h"
#include <vector>

class Renderer : public System<Renderer> {

public:

	struct ViewportSize {
		uint32_t width;
		uint32_t height;
	};

	Renderer() : m_Camera(glm::mat4(1.0f)) {}

	void Init(GLFWwindow*, ViewportSize);
	void Run();
	void Clear();
	void Clean();
	void SwapFramebuffer() const { glfwSwapBuffers(m_Window); }
	void ResizeViewport(int, int);

	unsigned int GetViewportImage() { return m_Framebuffer->GetColorAttachment(); }

private:
	
	OpenGL::Framebuffer* m_Framebuffer;
	OpenGL::Camera m_Camera;

	GLFWwindow* m_Window;

	void Draw();

	std::vector<OpenGL::GameObject> m_RenderObjects;

	

};

