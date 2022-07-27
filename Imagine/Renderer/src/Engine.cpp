#include "Engine.h"
#include <stdexcept>

void Engine::Init() {

	glfwInit();

	m_Window = glfwCreateWindow(1280, 860, "OpenGL", nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to init GLAD");
		return;
	}

	Renderer::Get().Init(m_Window, { 400, 300 });
	
	m_UI.Init(m_Window);
}

void Engine::Run() {


	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Get().Clear();

		glfwPollEvents();

		Renderer::Get().Run();
		m_UI.Render();

		Renderer::Get().SwapFramebuffer();

	}
}

void Engine::Clean() {
	//m_Renderer.Clean();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


Engine::~Engine() {
	//m_Renderer.Clean();
}

