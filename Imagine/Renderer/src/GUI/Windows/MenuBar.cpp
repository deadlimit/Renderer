#include "MenuBar.h"
#include <iostream>

void MenuBar::Render() {

	ImGui::BeginMainMenuBar();
	
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Open", "Ctrl+F")) { std::cout << "Open" << std::endl; }
		if (ImGui::MenuItem("Save", "Ctrl+S")) { std::cout << "Save" << std::endl; }
		if (ImGui::MenuItem("Close", "Ctrl+S")) { std::cout << "Close" << std::endl; }

		ImGui::EndMenu();
	}

	//Need someway to pass command to renderer
	if (ImGui::BeginMenu("Load object")) {
		if (ImGui::MenuItem("Square")) { std::cout << "Load Square!" << std::endl; }
		if (ImGui::MenuItem("Triangle")) { std::cout << "Load Triangle" << std::endl; }
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Styles")) {
		if (ImGui::MenuItem("Dark")) { ImGui::StyleColorsDark(); }
		if (ImGui::MenuItem("Light")) { ImGui::StyleColorsLight(); }
		if (ImGui::MenuItem("Classic")) { ImGui::StyleColorsClassic(); }
		ImGui::EndMenu();
	}



	ImGui::EndMainMenuBar();
}
