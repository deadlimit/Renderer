#pragma once


#include "Subsystems/Renderer/Renderer.h"
#include "Subsystems//GUI/GUI.h"
#include "glad.h"
#include "glfw3.h"
#include <map>

class Engine {

public:
	Engine() : m_Camera(glm::mat4(1.0f)) {}
	~Engine();

	void Init();
	void Run();
	void Clean();

private:

	RenderInformation test;

	void SubitForRendering();
	
	GLFWwindow* m_Window;

	OpenGL::Camera m_Camera;
};


