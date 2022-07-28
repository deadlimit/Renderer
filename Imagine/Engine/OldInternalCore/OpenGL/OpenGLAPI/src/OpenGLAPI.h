#pragma once

#include "OpenGLCore.h"
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Framebuffer.h"

struct GLFWwindow;

namespace OpenGL {

	class GraphicsAPI {

	public:
		GraphicsAPI();

		void Init(GLFWwindow*, uint32_t, uint32_t);
		void Run();
		void Clear();
		void Clean();
		
		const Framebuffer& FrameBuffer() const { return *m_Framebuffer; }

	private:

		void DrawObjects();

	private:

		GLFWwindow* m_Window;
		Framebuffer* m_Framebuffer;
		Camera m_Camera;

		//This should not be gameobjects, make more atomic
		std::vector<GameObject> m_RenderObjects;

	};


}