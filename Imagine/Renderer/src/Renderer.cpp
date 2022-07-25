#include "Renderer.h"
#include <iostream>


Renderer::Renderer() {
	RenderAPI = new API::GraphicsAPI();
}

void Renderer::Init(GLFWwindow* window) {
	RenderAPI->Init(window);
}

void Renderer::Run() {
	RenderAPI->Run();
}

void Renderer::Clear() {
	RenderAPI->Clear();
}

void Renderer::Clean() {
	RenderAPI->Clean();
}
