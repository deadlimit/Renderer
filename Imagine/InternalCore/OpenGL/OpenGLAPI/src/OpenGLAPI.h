#pragma once

#include "OpenGLCore.h"
#include <vector>
#include "GameObject.h"
#include "Camera.h"

struct GLFWwindow;

namespace OpenGL {

	class GraphicsAPI {

	public:
		GraphicsAPI();

		void Init();
		void Run();
		void Clear();
		void Clean();
		GLFWwindow& GetWindow() const { return *m_Window; }

	private:

		void DrawObjects();

	private:

		GLFWwindow* m_Window;

		Camera m_Camera;

		//This should not be gameobjects, make more atomic
		std::vector<GameObject> m_RenderObjects;

	};


}