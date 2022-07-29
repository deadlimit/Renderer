#pragma once

#include "glad.h"
#include "glfw3.h"
#include <vector>
#include <string>

namespace GUI {

	void Init(GLFWwindow*);
	void PrintToConsole(const std::string&);
	void Draw();
	void Shutdown();
}




