#include "Viewport.h"

void Viewport::Render() {

	ImGui::Begin("Viewport", &m_IsOpen);

	ImVec2 pos = ImGui::GetCursorScreenPos();

	ImGui::Image((void*)m_RenderID, ImGui::GetContentRegionAvail());


	ImGui::End();

}
