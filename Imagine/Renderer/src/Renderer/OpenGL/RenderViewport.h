#pragma once
#include "OpenGLCore.h"
#include "Framebuffer.h"
#include <tuple>

namespace OpenGL {
	class RenderViewport {

	public:
		RenderViewport(uint32_t, uint32_t);

		void Resize(uint32_t, uint32_t);

		uint32_t GetRenderID() const {return m_Framebuffer->GetColorAttachment();}
		
		void Bind() const;
		void Unbind() const;

		std::tuple<uint32_t, uint32_t> GetSize() const { return { m_CurrentWidth, m_CurrentHeight }; }

		void Clear() const;

	private:

		bool m_Initialized;

		uint32_t m_CurrentWidth;
		uint32_t m_CurrentHeight;


		Framebuffer* m_Framebuffer;

	};
}

