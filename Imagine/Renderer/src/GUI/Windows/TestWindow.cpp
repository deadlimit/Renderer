#include "TestWindow.h"
#include <iostream>

void TestWindow::Render() {

	
	ImGui::Begin("Hello world", &m_IsOpen, ImGuiWindowFlags_MenuBar);

	ImGui::End();

}
