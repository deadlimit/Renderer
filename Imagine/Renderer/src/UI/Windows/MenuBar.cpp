#include "MenuBar.h"

#include <iostream>

void MenuBar::Render() {

	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("File", true)) {
		if (ImGui::MenuItem("Open", "Ctrl+F")) { std::cout << "Open" << std::endl; }
		if (ImGui::MenuItem("Save", "Ctrl+S")) { std::cout << "Save" << std::endl; }

		ImGui::EndMenu();

	}



	ImGui::EndMainMenuBar();
}
