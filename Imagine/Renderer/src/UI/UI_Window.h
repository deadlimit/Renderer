#pragma once

#include "imgui.h"

class UI_Window {

public:

	UI_Window() {}
	virtual void Render() = 0;
	virtual ~UI_Window() {}

};

