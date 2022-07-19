#pragma once


#include <vector>

class GUIElement;

class GUI {

public:

	GUI(class GLFWwindow&);

	void AddElement(GUIElement*);

	void Draw();
	
private:

	//use better data structure
	std::vector<GUIElement*> m_GUIElements;

};
