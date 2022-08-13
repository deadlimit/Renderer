#include "GUI.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Subsystems/Renderer/Renderer.h"
#include "Engine.h"
#include "Subsystems/EntityManager.h"
#include "EngineData/EngineData.h"
#include <filesystem>
#include "Subsystems/EditorCamera/EditorCamera.h"

#define IMGUI_IMPL_OPENGL_ES3

static std::vector<std::string> g_ConsoleMessages;
static uint32_t g_ViewportImageID;

static void BeginFrame();
static void EndFrame();

static bool Open_SceneWindow = true;
static bool Open_Viewport = true;
static bool Open_Console = true;
static bool Open_Stats = true;
static bool g_ViewportIsFocused = false;
static int32_t selected_entity_ID = -1;

void GUI::Init(GLFWwindow* window) {

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplGlfw_InitForOpenGL(window, false);

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


void Draw_Toolbar() {
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
		if (ImGui::MenuItem("Viewport")) { Open_Viewport = true; }
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
void Draw_Viewport() {

	if (!g_ViewportImageID)
		g_ViewportImageID = Renderer::Framebuffer.ColorAttachment;

	ImGui::Begin("Viewport", &Open_Viewport);

	ImGuiIO& io = ImGui::GetIO();

	ImVec2& vMin = ImGui::GetWindowContentRegionMin();
	ImVec2& vMax = ImGui::GetWindowContentRegionMax();

	vMin.x += ImGui::GetWindowPos().x;
	vMin.y += ImGui::GetWindowPos().y;
	vMax.x += ImGui::GetWindowPos().x;
	vMax.y += ImGui::GetWindowPos().y;

	EngineData::g_ViewportData.Position = { vMin.x, vMin.y, vMax.x, vMax.y };

	if (ImGui::IsWindowFocused()) {
		io.WantCaptureKeyboard = false;
		io.WantCaptureMouse = false;

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
	} else {
		io.WantCaptureKeyboard = true;
		io.WantCaptureMouse = true;
	}

	float x = vMax.x - vMin.x;
	float y = vMax.y - vMin.y;

	//TODO MOVE THIS TO RENDERER, SO IT CAN CHECK ITSELF
	Renderer::ResizeViewport((vMax.x - vMin.x), (vMax.y - vMin.y));

	EngineData::g_ViewportData.Size = { x, y };

	ImGui::Image((void*)g_ViewportImageID, ImVec2(x, y), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}
void Draw_Stats() {

	static bool open = true;

	ImGui::Begin("Viewport stats", &open, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Text("Viewport IMGUI: %.0f | %.0f", (float)EngineData::g_ViewportData.Size.x, (float)EngineData::g_ViewportData.Size.y);
	ImGui::Spacing();
	ImGui::Text("Camera position   %.2f, %.2f, %.2f", EditorCamera::Params.Position.x, EditorCamera::Params.Position.y, EditorCamera::Params.Position.z);
	ImGui::Text("Camera forward   %.2f, %.2f, %.2f", EditorCamera::Params.Forward.x, EditorCamera::Params.Forward.y, EditorCamera::Params.Forward.z);
	ImGui::Text("Camera up   %.2f, %.2f, %.2f", EditorCamera::Params.Up.x, EditorCamera::Params.Up.y, EditorCamera::Params.Up.z);
	ImGui::Text("Camera pitch %.0f", EditorCamera::Params.Pitch);
	ImGui::Text("Camera yaw   %.0f", EditorCamera::Params.Yaw);

	ImGui::End();
}
void Draw_SceneHeirarchy() {

	static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
	static uint32_t clicked_ID = 0;
	static bool fold_out = 1;
	
	ImGui::Begin("Scene", &Open_SceneWindow);

	ImGui::SetNextItemOpen(fold_out);

	if (ImGui::TreeNode("Scene name")) {

		ImGui::Indent(10);

		for (int i = 0; i < EntityManager::Entities.size(); ++i) {
			ImGui::Selectable(EntityManager::Entities[i].Name.c_str(), false);

			if (ImGui::IsItemClicked()) {
				selected_entity_ID = EntityManager::Entities[i].ID;
			}

		}

		ImGui::TreePop();
	}


	ImGui::End();

}
void Draw_ContentBrowser() {
	ImGui::Begin("Content browser");

	ImGui::End();
}
void Draw_ConsoleWindow() {
	ImGui::Begin("Console", &Open_Console);

	if (ImGui::Button("Clear console"))
		g_ConsoleMessages.clear();
	ImGui::SameLine();
	if (ImGui::Button("Test button"))
		GUI::PrintToConsole("Test message");

	for (int i = 0; i < g_ConsoleMessages.size(); ++i) {
		ImGui::Text(g_ConsoleMessages[i].c_str());
	}

	ImGui::End();
}
void Draw_Inspector() {

	ImGui::Begin("Inspector");

	if (selected_entity_ID >= 0) {
		ImGui::Text(EntityManager::Entities[selected_entity_ID].Name.c_str());
		ImGui::Text("Transform");
		ImGui::SameLine();
		float transform[3] = {
		EntityManager::RenderingData[selected_entity_ID].transform[3][0],
		EntityManager::RenderingData[selected_entity_ID].transform[3][1],
		EntityManager::RenderingData[selected_entity_ID].transform[3][2]
		};
		ImGui::DragFloat3("Transform", transform, 0.005f, -200.0f, 200.0f, "%.3f", 0);

		EntityManager::RenderingData[selected_entity_ID].transform[3][0] = transform[0];
		EntityManager::RenderingData[selected_entity_ID].transform[3][1] = transform[1];
		EntityManager::RenderingData[selected_entity_ID].transform[3][2] = transform[2];


		//ImGui::DragFloat4("Transform", );

	}


	ImGui::End();
}

void GUI::Draw() {

	BeginFrame();

	ImGui::DockSpaceOverViewport();

	Draw_Toolbar();
	Draw_Viewport();
	Draw_Stats();
	Draw_SceneHeirarchy();
	Draw_ContentBrowser();
	Draw_ConsoleWindow();
	Draw_Inspector();


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
