#include "GUI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GUIWindow.h"
#include "Windows/TestWindow.h"
#include "Windows/Viewport.h"
#include "Windows/ConsoleWindow.h"
#include <iostream>
#include "glad.h"
#include "glfw3.h"
#include "../../../Renderer/src/Renderer/Renderer.h"
#include <sstream>
#include <iomanip>
#define IMGUI_IMPL_OPENGL_ES3


void GUI::Init(GLFWwindow* window) {

	m_Window = window;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
	ImGui::StyleColorsDark();

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	TestWindow* test = new TestWindow();
	Viewport* viewport = new Viewport();
	ConsoleWindow* console = new ConsoleWindow();

	m_Subwindows["Viewport"] = viewport;
	m_Subwindows["TestWindow"] = test;
	m_Subwindows["Console"] = console;
}

void GUI::Render() {

	BeginFrame();

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

	if (ImGui::BeginMenu("Windows")) {
		if (ImGui::MenuItem("Console")) { std::cout << "Console" << std::endl; }
		if (ImGui::MenuItem("Viewport")) { std::cout << "Viewport" << std::endl; }
		ImGui::EndMenu();
	}
	

	if (ImGui::BeginMenu("Styles")) {
		if (ImGui::MenuItem("Dark")) { ImGui::StyleColorsDark(); }
		if (ImGui::MenuItem("Light")) { ImGui::StyleColorsLight(); }
		if (ImGui::MenuItem("Classic")) { ImGui::StyleColorsClassic(); }
		ImGui::EndMenu();
	}


	ImGui::EndMainMenuBar();

	ImGui::DockSpaceOverViewport();

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

void GUI::PrintToConsole(const std::string& message) {
	static_cast<ConsoleWindow*>(GUI::Get().GetWindow("Console"))->AddMessage(message);
}

GUIWindow* GUI::GetWindow(const std::string& windowName) {
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

