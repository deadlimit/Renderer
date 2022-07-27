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

	Renderer::Get().Init(m_Window, { 300, 300 });
	GUI::Get().Init(m_Window);

}

void Engine::Run() {


	while (!glfwWindowShouldClose(m_Window)) {

		Renderer::Get().Clear();

		glfwPollEvents();

		Renderer::Get().Run();
		GUI::Get().Render();

		Renderer::Get().SwapFramebuffer();

	}
}

void Engine::Clean() {

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}


Engine::~Engine() {
}

