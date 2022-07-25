#pragma once

#include "Renderer.h"
#include "GUI/GUI.h"

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

	GUI m_UI;

};

