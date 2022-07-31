#pragma once


#include "Subsystems/Renderer/Renderer.h"

#include "glad.h"
#include "glfw3.h"
#include <map>


class Engine {

public:
	Engine() : m_Window(nullptr), m_Camera(glm::mat4(1.0f)) {}
	~Engine() {}

	void Init();
	void Run();
	void Clean();

private:



	GLFWwindow* m_Window;

	Renderer::Camera m_Camera;
};


