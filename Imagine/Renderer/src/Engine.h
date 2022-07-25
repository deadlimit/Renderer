#pragma once

#include "Renderer.h"
#include "UI/UI.h"

class Engine {

public:
	Engine() = default;
	~Engine();
	
	void Init();
	void Run();
	void Clean();

	
private:

	Renderer m_Renderer;
	GLFWwindow* m_Window;

	UI m_UI;

};

