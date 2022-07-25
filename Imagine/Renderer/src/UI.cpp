#include "UI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <iostream>

#define IMGUI_IMPL_OPENGL_ES3

void UI::Init(GLFWwindow* window) {

	m_Window = window;

	IMGUI_CHECKVERSION();
	auto context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);
	ImGuiIO& io = ImGui::GetIO(); 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      	


	ImGui_ImplGlfw_InitForOpenGL(m_Window, false);
	ImGui_ImplOpenGL3_Init("#version 460 core");
	ImGui::StyleColorsDark();

	ImGui::SetNextWindowSize({ 300, 300 });
}

void UI::Render() {

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	
	ImGui::Begin("Hello, world!");
	
	ImGui::Button("Button on window B");

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

UI::~UI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}