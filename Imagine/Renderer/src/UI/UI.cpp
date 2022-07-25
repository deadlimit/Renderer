#include "UI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "UI_Window.h"
#include "Windows/MenuBar.h"

#include <iostream>

#define IMGUI_IMPL_OPENGL_ES3

void UI::Init(GLFWwindow* window) {

	m_Window = window;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
	

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();

	MenuBar* bar = new MenuBar();

	m_Subwindows.push_back(bar);

}

void UI::Render() {

	BeginFrame();

	for (int i = 0; i < m_Subwindows.size(); ++i) {
		m_Subwindows[i]->Render();
	}

	EndFrame();
}

void UI::BeginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UI::EndFrame() {
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::~UI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}