#include "GUI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../Subsystems/Renderer/Renderer.h"

#define IMGUI_IMPL_OPENGL_ES3

static std::vector<std::string> g_ConsoleMessages;
static uint32_t g_ViewportImageID;

static void BeginFrame();
static void EndFrame();

void GUI::Init(GLFWwindow* window) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

}

void GUI::PrintToConsole(const std::string& message) {
	
	time_t t = std::time(nullptr);
	tm tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%H:%M:%S");
	std::string timeString = oss.str();

	timeString.append(" " + message);

	g_ConsoleMessages.push_back(timeString);

}

void GUI::Draw() {

	BeginFrame();

	ImGui::DockSpaceOverViewport();

	#pragma region TopMenuBar
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
#pragma endregion

	#pragma region Viewport 

		if (!g_ViewportImageID)
			g_ViewportImageID = Renderer::Framebuffer.ColorAttachment;

		ImGui::Begin("Viewport");

		//ImVec2 pos = ImGui::GetCursorScreenPos();

		const ImVec2& viewportWindowSize = ImGui::GetContentRegionAvail();
	
		Renderer::ResizeViewport(viewportWindowSize.x, viewportWindowSize.y);

		ImGui::Image((void*)g_ViewportImageID, viewportWindowSize, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();

	#pragma endregion

	#pragma region Stats

		static bool open = true;

		ImGui::Begin("Viewport stats",&open, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Viewport IMGUI: %.0f | %.0f", viewportWindowSize.x, viewportWindowSize.y);

		ImGui::End();

	#pragma endregion

	#pragma region Scene 
			ImGui::Begin("Scene");

			ImGui::End();
	#pragma endregion

	#pragma region ConsoleWindow

		ImGui::Begin("Console");

		if (ImGui::Button("Clear console"))
			g_ConsoleMessages.clear();
		ImGui::SameLine();
		if (ImGui::Button("Test button"))
			PrintToConsole("Test message");

		for (int i = 0; i < g_ConsoleMessages.size(); ++i) {
			ImGui::Text(g_ConsoleMessages[i].c_str());
		}


		ImGui::End();

	#pragma endregion

	EndFrame();

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);

	}

}


static void BeginFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

static void EndFrame() {

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Shutdown() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
