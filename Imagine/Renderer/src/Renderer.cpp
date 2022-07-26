#include "Renderer.h"
#include <iostream>


Renderer::Renderer() {
	RenderAPI = new API::GraphicsAPI();
}

void Renderer::Init(GLFWwindow* window, unsigned int width, unsigned int height) {
	RenderAPI->Init(window, width, height);
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
