#pragma once

#include "../System.h"
#include "OpenGL/OpenGLCore.h"
#include "OpenGL/GameObject.h"
#include "OpenGL/Camera.h"
#include "OpenGL/RenderViewport.h"
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
	void SwapFramebuffer() const;
	void ResizeViewport(int, int);

	ViewportSize GetViewportSize() const { auto [width, height] = m_RenderViewport->GetSize(); return { width, height }; }

	unsigned int GetViewportImage() { return m_RenderViewport->GetRenderID(); }

private:

	OpenGL::RenderViewport* m_RenderViewport;
	OpenGL::Camera m_Camera;

	GLFWwindow* m_Window;

	std::vector<OpenGL::GameObject> m_RenderObjects;

};
