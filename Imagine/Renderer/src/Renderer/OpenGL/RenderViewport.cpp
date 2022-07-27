#include "RenderViewport.h"

namespace OpenGL {

	RenderViewport::RenderViewport(uint32_t width, uint32_t height) : m_CurrentWidth(width), m_CurrentHeight(height), m_Initialized(false) {

		m_Framebuffer = new Framebuffer(width, height);

		Resize(width, height);

		m_Initialized = true;

	}
	
	void RenderViewport::Resize(uint32_t width, uint32_t height) {

		if (m_Initialized && (width == m_CurrentWidth && height == m_CurrentHeight))
			return;

		m_CurrentWidth = width;
		m_CurrentHeight = height;

		glViewport(0, 0, m_CurrentWidth, m_CurrentHeight);
		
		m_Framebuffer->RecreateFramebuffer(m_CurrentWidth, m_CurrentHeight);

	}

	void RenderViewport::Bind() const {
		m_Framebuffer->Bind();
	}

	void RenderViewport::Unbind() const {
		m_Framebuffer->Unbind();
	}

	void RenderViewport::Clear() const {
		m_Framebuffer->Bind();
		glClear(GL_COLOR_BUFFER_BIT);
		m_Framebuffer->Unbind();
	}

}
