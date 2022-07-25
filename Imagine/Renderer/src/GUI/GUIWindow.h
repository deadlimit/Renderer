#pragma once

#include "imgui.h"

class GUIWindow {

public:

	GUIWindow() {}
	virtual void Render() = 0;
	virtual ~GUIWindow() {}

};

