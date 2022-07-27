#pragma once
#include "OpenGLCore.h"

namespace OpenGL {

	class Framebuffer {

	public:
		Framebuffer(uint32_t, uint32_t);
		~Framebuffer();
		
		void Bind() const;
		void Unbind() const;
		
		uint32_t GetColorAttachment() const { return m_ColorAttachmentID; }

	private:

		uint32_t m_FramebufferID;
		uint32_t m_ColorAttachmentID;
		uint32_t m_DepthAttachmentID;
		
	};

}


