#include "GUI.h"
#include "GUIElement.h"
#include "../../VulkanCore.h"

GUI::GUI(GLFWwindow& window) {

}

void GUI::AddElement(GUIElement* element) {
	m_GUIElements.push_back(element);
}

void GUI::Draw() {
	/*
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < m_GUIElements.size(); ++i)
		m_GUIElements[i]->Draw();

	ImGui::Render();
	*/
}
