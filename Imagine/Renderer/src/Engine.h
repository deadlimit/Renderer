#pragma once

#include "Renderer/Renderer.h"
#include "GUI/GUI.h"
#include "glad.h"
#include "glfw3.h"

class Engine {

public:
	Engine() = default;
	~Engine();

	void Init();
	void Run();
	void Clean();


private:

	GLFWwindow* m_Window;

};


