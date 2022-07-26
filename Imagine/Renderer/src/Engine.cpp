#include "Engine.h"
#include "GUI/Windows/Viewport.h"

void Engine::Init() {

	glfwInit();

	m_Window = glfwCreateWindow(1280, 860, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	m_Renderer.Init(m_Window, 300, 300);
	m_UI.Init(m_Window);

	reinterpret_cast<Viewport*>(m_UI.GetWindow("Viewport"))->SetRenderID(m_Renderer.GetRenderImage());

	

}

void Engine::Run() {


	while (!glfwWindowShouldClose(m_Window)) {

		m_Renderer.Clear();
		
		glfwPollEvents();
	
		m_Renderer.Run();
		m_UI.Render();
	}
}

void Engine::Clean() {
	m_Renderer.Clean();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


Engine::~Engine() {
	m_Renderer.Clean();
}

