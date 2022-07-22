#include "Engine.h"


void Engine::Init() {
	m_Renderer.Init();
	m_Window = &m_Renderer.GetWindow();
}

void Engine::Run() {

	while (!glfwWindowShouldClose(m_Window)) {

		m_Renderer.Run();


	}

	
}

void Engine::Clean() {
	m_Renderer.Clean();
}

Engine::~Engine() {
	m_Renderer.Clean();
}