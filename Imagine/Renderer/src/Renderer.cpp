#include "Renderer.h"
#include <iostream>
#include "VulkanAPi.h"

Renderer::Renderer(API API) : RenderAPI(nullptr) {

	switch (API) {
		case API::OPENGL:
			std::cout << "Using OpenGL" << std::endl;
			//RenderAPI = new OpenGLAPI();
			break;
		case API::VULKAN:
			std::cout << "Using Vulkan" << std::endl;
			RenderAPI = new VulkanAPI();
	};
}

void Renderer::Init() {
	RenderAPI->Init();
}

void Renderer::Run() {
	RenderAPI->Run();
}

void Renderer::Clean() {
	RenderAPI->Clean();
}
