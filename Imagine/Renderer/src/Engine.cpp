#include "Engine.h"

void Engine::Init() {
	m_Renderer.Init();
	m_Window = &m_Renderer.GetWindow();
	m_UI.Init(m_Window);
}

void Engine::Run() {

	while (!glfwWindowShouldClose(m_Window)) {
		
		m_Renderer.Clear();
		m_UI.Render();
		m_Renderer.Run();
	}
}

void Engine::Clean() {
	m_Renderer.Clean();
}

Engine::Engine() {
	
}

Engine::~Engine() {
	m_Renderer.Clean();
}