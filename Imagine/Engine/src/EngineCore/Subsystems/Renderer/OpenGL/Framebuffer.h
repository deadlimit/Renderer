#pragma once
#include "OpenGLCore.h"

namespace Renderer {

	class Framebuffer {

	public:
		Framebuffer(uint32_t, uint32_t);
		~Framebuffer();
		
		void Bind() const;
		void Unbind() const;
		
		void RecreateFramebuffer(uint32_t, uint32_t);

		uint32_t GetColorAttachment() const { return m_ColorAttachmentID; }

	private:

		uint32_t m_FramebufferID = 0;
		uint32_t m_ColorAttachmentID = 0;
		uint32_t m_DepthAttachmentID = 0;
		
	};

}


