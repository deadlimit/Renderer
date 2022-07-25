#include "GUI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GUIWindow.h"
#include "Windows/MenuBar.h"
#include "Windows/TestWindow.h"
#include "Windows/Viewport.h"
#include <iostream>

#define IMGUI_IMPL_OPENGL_ES3

void GUI::Init(GLFWwindow* window) {

	m_Window = window;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();



	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	MenuBar* bar = new MenuBar();
	TestWindow* test = new TestWindow();
	Viewport* viewport = new Viewport();

	m_Subwindows["Viewport"] = viewport;
	m_Subwindows["TestWindow"] = bar;
	m_Subwindows["MenuBar"] = test;
}

void GUI::Render() {

	BeginFrame();

	for (std::map<std::string, GUIWindow*>::iterator it = m_Subwindows.begin(); it != m_Subwindows.end(); ++it) {

		if (it->second->IsOpen()) {
			it->second->Render();
		}

	}

	EndFrame();

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);

	}

}

GUIWindow const* GUI::GetWindow(const std::string& windowName) {
	if (m_Subwindows.find(windowName) != m_Subwindows.end()) {
		return m_Subwindows[windowName];
	}

	return nullptr;
}

void GUI::BeginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::EndFrame() {
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GUI::~GUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}