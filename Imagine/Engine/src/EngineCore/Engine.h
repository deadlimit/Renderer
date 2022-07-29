#pragma once


#include "Subsystems/Renderer/Renderer.h"

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

	Renderer::RenderInformation test;
	
	GLFWwindow* m_Window;

	OpenGL::Camera m_Camera;
};


