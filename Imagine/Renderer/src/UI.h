#pragma once

#include "glfw3.h"

class UI {

public:

	UI() = default;	
	~UI();

	void Init(GLFWwindow*);

	void Render();

private:

	GLFWwindow* m_Window;

};

