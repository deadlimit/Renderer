#include "Renderer.h"
#include <iostream>


Renderer::Renderer() : RenderAPI(nullptr) {
	RenderAPI = new API::GraphicsAPI();
}

void Renderer::Init() {
	RenderAPI->Init();
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
