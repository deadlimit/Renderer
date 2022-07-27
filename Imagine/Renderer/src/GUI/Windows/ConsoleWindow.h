#pragma once

#include "../GUIWindow.h"
#include <vector>
#include <string>

class ConsoleWindow : public GUIWindow {

public:

	virtual void Render() override;

	void AddMessage(const std::string&);

private:



	std::vector<std::string> m_ConsoleMessageQueue;

};


