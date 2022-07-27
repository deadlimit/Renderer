#pragma once
#include "../GUIWindow.h"

class Viewport : public GUIWindow {

public:

	void SetRenderID(unsigned int ID) { m_RenderID = ID; }

	virtual void Render() override;

private:

	unsigned int m_RenderID;

};




