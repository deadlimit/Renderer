#include "Viewport.h"
#include "../../Renderer/Renderer.h"

void Viewport::Render() {

	if (!m_RenderID)
		m_RenderID = Renderer::Get().GetViewportImage();

	ImGui::Begin("Viewport", &m_IsOpen);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	m_Size = ImGui::GetContentRegionAvail();
	m_Position = ImGui::GetWindowPos();

	Renderer::Get().ResizeViewport(m_Size.x, m_Size.y);

	ImGui::Image((void*)m_RenderID, m_Size, ImVec2(0, 1), ImVec2(1, 0));


	ImGui::End();

}

