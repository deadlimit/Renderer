#include "Framebuffer.h"
#include <iostream>

namespace OpenGL {

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

		if (m_FramebufferID) {

			glDeleteFramebuffers(1, &m_FramebufferID);
			glDeleteTextures(1, &m_ColorAttachmentID);

		}

		glGenFramebuffers(1, &m_FramebufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);


		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachmentID);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachmentID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachmentID, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			throw std::runtime_error("Failed to recreate framebuffer");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}


}

