#include "TestWindow.h"
#include <iostream>
#include "../GUI.h"
#include "../../Renderer/Renderer.h"

void TestWindow::Render() {

	ImGui::Begin("Viewport stats", &m_IsOpen, ImGuiWindowFlags_AlwaysAutoResize);

	uint32_t width = Renderer::Get().GetViewportSize().width;
	uint32_t height = Renderer::Get().GetViewportSize().height;

	ImGui::Text("Viewport OpenGL: %d | %d", width, height);

	const ImVec2& viewportWindowSize = GUI::Get().GetWindow("Viewport")->GetWindowSize();

	ImGui::Text("Viewport IMGUI: %.0f | %.0f", viewportWindowSize.x, viewportWindowSize.y);

	ImGui::End();

}


