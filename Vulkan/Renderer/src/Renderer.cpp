#include "Renderer.h"
#include "Vulkan/VulkanAPI.h"

#include <iostream>

Renderer::Renderer(API API) : RenderAPI(nullptr) {

	switch (API) {
		case API::OPENGL:
			std::cout << "OpenGL not implemented yet" << std::endl;
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
