#pragma once
#include <vector>

#if defined(VULKAN)
	#include "VulkanAPI.h"
	#define API Vulkan
#elif defined(OPENGL)
	#include "OpenGLAPI.h"
	#define API OpenGL
#else
	#error Error: no graphics-API defined
#endif

class Renderer {

public:

	Renderer();

	void Init(GLFWwindow*);
	void Run();
	void Clear();
	void Clean();
	
private:

	API::GraphicsAPI* RenderAPI;

};

