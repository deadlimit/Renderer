#pragma once

#include "imgui.h"


class GUIWindow {

public:

	GUIWindow() : m_IsOpen(true) {}
	virtual void Render() = 0;
	virtual ~GUIWindow() {}

	const ImVec2& GetWindowSize() const { return m_Size; }
	const ImVec2& GetWindowPosition() const { return m_Position; }

	bool IsOpen() const { return m_IsOpen; }

protected:

	ImVec2 m_Size;
	ImVec2 m_Position;
	bool m_IsOpen;

};


