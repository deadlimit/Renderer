#pragma once


#include <vector>
#include "GUIWindow.h"
#include <map>
#include <string>
#include "../System.h"

class GUI : public System<GUI> {

public:

	GUI() = default;
	~GUI();

	void Init(struct GLFWwindow*);

	void Render();

	GUIWindow* GetWindow(const std::string&);

private:

	void BeginFrame();
	void EndFrame();

private:

	std::map<std::string, GUIWindow*> m_Subwindows;

	GLFWwindow* m_Window;

};




