#pragma once
#include <vector>

class GraphicsAPI;

enum class API {
	OPENGL = 0, 
	VULKAN = 1
};

class Renderer {

public:

	Renderer(API);

	void Init();
	void Run();
	void Clean();

private:

	GraphicsAPI* RenderAPI;

};

