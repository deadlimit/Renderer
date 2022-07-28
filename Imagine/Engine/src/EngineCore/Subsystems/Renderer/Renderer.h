#pragma once

#include "../../System.h"
#include "OpenGL/OpenGLCore.h"
#include "OpenGL/Camera.h"
#include "OpenGL/RenderViewport.h"
#include "OpenGL/Mesh.h"
#include "OpenGL/Primitives.h"
#include <vector>

class Renderer : public System<Renderer> {

public:

	struct ViewportSize {
		uint32_t width;
		uint32_t height;
	};

	void Init(GLFWwindow*, ViewportSize);
	void Draw(const OpenGL::Mesh&);
	void Clear();
	void Clean();
	void SwapFramebuffer() const;
	void ResizeViewport(int, int);

	const OpenGL::RenderViewport& GetViewport() const { return *m_RenderViewport; }
	ViewportSize GetViewportSize() const { auto [width, height] = m_RenderViewport->GetSize(); return { width, height }; }
	unsigned int GetViewportImage() { return m_RenderViewport->GetRenderID(); }

private:

	OpenGL::RenderViewport* m_RenderViewport;

	GLFWwindow* m_Window;

};
