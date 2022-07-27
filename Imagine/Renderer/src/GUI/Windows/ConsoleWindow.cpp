#include "ConsoleWindow.h"
#include "imgui.h"
#include <sstream>
#include <iomanip>
#include <iostream>

void ConsoleWindow::Render() {

	ImGui::Begin("Console");

	if (ImGui::Button("Clear console"))
		m_ConsoleMessageQueue.clear();

	for (int i = 0; i < m_ConsoleMessageQueue.size(); ++i) {			
		ImGui::Text(m_ConsoleMessageQueue[i].c_str());
	}

	ImGui::End();
	
}

void ConsoleWindow::AddMessage(const std::string& message) {

	time_t t = std::time(nullptr);
	tm tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%H:%M:%S");
	std::string timeString = oss.str();

	timeString.append(" " + message);

	m_ConsoleMessageQueue.push_back(timeString);
}


