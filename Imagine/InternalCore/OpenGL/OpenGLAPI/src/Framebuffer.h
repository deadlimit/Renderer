#pragma once
#include "OpenGLCore.h"

namespace OpenGL {

	class Framebuffer {

	public:
		Framebuffer(uint32_t, uint32_t);
		~Framebuffer();
		
		void Bind(bool) const;
		
	private:

		unsigned int m_FramebufferID;
		unsigned int m_ColorAttachmentID;
		unsigned int m_DepthAttachmentID;
		
	};

}


