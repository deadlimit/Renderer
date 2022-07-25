#pragma once

#include "glfw3.h"
#include <vector>
#include "UI_Window.h"

class UI {

public:

	UI() = default;	
	~UI();
	
	void Init(GLFWwindow*);

	void Render();

private:

	void BeginFrame();
	void EndFrame();

private:
	
	std::vector<UI_Window*> m_Subwindows;

	GLFWwindow* m_Window;

};

