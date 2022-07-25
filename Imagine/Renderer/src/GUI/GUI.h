#pragma once

#include "glfw3.h"
#include <vector>
#include "GUIWindow.h"

class GUI {

public:

	GUI() = default;	
	~GUI();
	
	void Init(GLFWwindow*);

	void Render();

private:

	void BeginFrame();
	void EndFrame();

private:
	
	std::vector<GUIWindow*> m_Subwindows;

	GLFWwindow* m_Window;

};

