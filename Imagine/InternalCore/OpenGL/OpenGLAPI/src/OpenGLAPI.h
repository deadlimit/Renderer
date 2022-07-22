#pragma once

#include "OpenGLCore.h"
#include <vector>
#include "GameObject.h"

struct GLFWwindow;

namespace OpenGL {

	class GraphicsAPI {

	public:
		void Init();
		void Run();
		void Clean();

		GLFWwindow& GetWindow() const { return *m_Window; }

	private:

		void DrawObjects();

	private:

		GLFWwindow* m_Window;

		std::vector<GameObject> m_RenderObjects;

	};


}