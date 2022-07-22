#pragma once

#include "glfw3.h"

class UI {

public:

	UI(GLFWwindow&);
	~UI();
	void Render() const;

private:

	GLFWwindow& m_Window;

};

