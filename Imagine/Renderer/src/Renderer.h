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

	void Init(GLFWwindow*, unsigned int, unsigned int);
	void Run();
	void Clear();
	void Clean();

	uint32_t GetRenderImage() const { return RenderAPI->FrameBuffer().GetColorAttachment(); }

private:

	API::GraphicsAPI* RenderAPI;

};

