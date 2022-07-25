#pragma once

#include "glfw3.h"
#include <vector>
#include "GUIWindow.h"
#include <map>
#include <string>

class GUI {

public:

	GUI() = default;	
	~GUI();
	
	void Init(GLFWwindow*);

	void Render();

	GUIWindow const* GetWindow(const std::string&);

private:
	
	void BeginFrame();
	void EndFrame();

private:
	
	std::map<std::string, GUIWindow*> m_Subwindows;

	GLFWwindow* m_Window;

};

