#include "Framebuffer.h"
#include <iostream>

namespace Renderer {

	Framebuffer::Framebuffer(uint32_t width, uint32_t height) {

		RecreateFramebuffer(width, height);

	}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &m_FramebufferID);

	}

	void Framebuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	}

	void Framebuffer::Unbind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::RecreateFramebuffer(uint32_t width, uint32_t height) {


	}


}

