#pragma once

#include "imgui.h"

class GUIWindow {

public:

	GUIWindow() : m_IsOpen(true) {}
	virtual void Render() = 0;
	virtual ~GUIWindow() {}

	bool IsOpen() const { return m_IsOpen; }

protected:

	bool m_IsOpen;

};

