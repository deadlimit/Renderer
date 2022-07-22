#pragma once

#include "Renderer.h"

class Engine {

public:

	~Engine();
	
	void Init();
	void Run();
	void Clean();

private:

	Renderer m_Renderer;
	GLFWwindow* m_Window;

};

