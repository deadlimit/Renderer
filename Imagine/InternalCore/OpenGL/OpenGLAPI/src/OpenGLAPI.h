#pragma once

#include "OpenGLCore.h"

struct GLFWwindow;

namespace OpenGL {

	class GraphicsAPI {

	public:
		void Init();
		void Run();
		void Clean();

	private:

		GLFWwindow* m_Window;

	};


}