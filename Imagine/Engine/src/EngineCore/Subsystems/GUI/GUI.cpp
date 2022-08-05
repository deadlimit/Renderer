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
#include "../Utils.h"
#include <filesystem>
#include "Subsystems/EditorCamera/EditorCamera.h"

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
static bool Open_SceneWindow = true;
static bool Open_Viewport = true;
static bool Open_Console = true;
static bool Open_Stats = true;
static bool g_ViewportIsFocused = false;

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
#pragma endregion

	#pragma region Viewport 
	
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

	Utils::g_InitParams.viewportMinPosition = { vMin.x, vMin.y };
	Utils::g_InitParams.viewportMaxPosition = { vMax.x, vMax.y };

	if (ImGui::IsWindowFocused()) {
		io.WantCaptureKeyboard = false;
		io.WantCaptureMouse = false;

		ImGui::GetForegroundDrawList()->AddRect(vMin, vMax, IM_COL32(255, 255, 0, 255));
	} else {
		io.WantCaptureKeyboard = true;
		io.WantCaptureMouse = true;
	}
		
	//Renderer::ResizeViewport(viewportWindowSize.x, viewportWindowSize.y);
	Renderer::ResizeViewport((vMax.x - vMin.x), (vMax.y - vMin.y));

	//Why initparams, makes no sense
	//TODO Make a better version

	Utils::g_InitParams.viewportWidth = vMax.x - vMin.x;
	Utils::g_InitParams.viewportHeight = (vMax.y - vMin.y);

	ImGui::Image((void*)g_ViewportImageID, ImVec2(Utils::g_InitParams.viewportWidth, Utils::g_InitParams.viewportHeight), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();

	#pragma endregion

	#pragma region Stats

		static bool open = true;

		ImGui::Begin("Viewport stats",&open, ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::Text("Viewport IMGUI: %.0f | %.0f", (float)Utils::g_InitParams.viewportWidth, (float)Utils::g_InitParams.viewportHeight);
		ImGui::Spacing();
		ImGui::Text("Camera pitch %.0f", EditorCamera::Rotation.x);
		ImGui::Text("Camera yaw   %.0f", EditorCamera::Rotation.y);
		ImGui::Text("Camera roll  %.0f", EditorCamera::Rotation.z);

		ImGui::End();

	#pragma endregion

	#pragma region Scene 
		
		static ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Leaf;
		static uint32_t clicked_ID = 0;
		static bool fold_out = 1;
		static int32_t selected_entity_ID = -1;
		ImGui::Begin("Scene", &Open_SceneWindow);

		ImGui::SetNextItemOpen(fold_out);

		if(ImGui::TreeNode("Scene name")) {
			   
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

	#pragma endregion

#pragma region ContentBrowser

		ImGui::Begin("Content browser");
		/*
		
		static const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
		static ImGuiTableFlags tableflags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;
		
		ImGui::BeginTable("Table", 3);

		// The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
		ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
		ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
		ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
		ImGui::TableHeadersRow();

		// Simple storage to output a dummy file-system.
		struct MyTreeNode {
			const char* Name;
			const char* Type;
			int			Size;
			int         ChildIdx;
			int         ChildCount;
			static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes) {
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				const bool is_folder = (node->ChildCount > 0);
				if (is_folder) {
					bool open = ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_SpanFullWidth);
					ImGui::TableNextColumn();
					ImGui::TextDisabled("--");
					ImGui::TableNextColumn();
					ImGui::TextUnformatted(node->Type);
					if (open) {
						for (int child_n = 0; child_n < node->ChildCount; child_n++)
							DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
						ImGui::TreePop();
					}
				} else {
					ImGui::TreeNodeEx(node->Name, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
					ImGui::TableNextColumn();
					ImGui::Text("%d", node->Size);
					ImGui::TableNextColumn();
					ImGui::TextUnformatted(node->Type);
				}
			}
		};
		static const MyTreeNode nodes[] =
		{
			{ "Root",                         "Folder",       -1,       1, 3    }, // 0
			{ "Music",                        "Folder",       -1,       4, 2    }, // 1
			{ "Textures",                     "Folder",       -1,       6, 3    }, // 2
			{ "desktop.ini",                  "System file",  1024,    -1,-1    }, // 3
			{ "File1_a.wav",                  "Audio file",   123000,  -1,-1    }, // 4
			{ "File1_b.wav",                  "Audio file",   456000,  -1,-1    }, // 5
			{ "Image001.png",                 "Image file",   203128,  -1,-1    }, // 6
			{ "Copy of Image001.png",         "Image file",   203256,  -1,-1    }, // 7
			{ "Copy of Image001 (Final2).png","Image file",   203512,  -1,-1    }, // 8
		};

		MyTreeNode::DisplayNode(&nodes[0], nodes);

		ImGui::EndTable();
		*/
		ImGui::End();


#pragma endregion

	#pragma region ConsoleWindow

		ImGui::Begin("Console", &Open_Console);

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

#pragma region Inspector


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
			ImGui::DragFloat3("Transform", transform, 0.005f, -200.0f, 200.0f,"%.3f", 0);
			


			EntityManager::RenderingData[selected_entity_ID].transform[3][0] = transform[0];
			EntityManager::RenderingData[selected_entity_ID].transform[3][1] = transform[1];
			EntityManager::RenderingData[selected_entity_ID].transform[3][2] = transform[2];


			//ImGui::DragFloat4("Transform", );

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
