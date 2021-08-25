#include "StatusPanel.h"
#include "Arc/Renderer/Renderer2D.h"

#include <imgui/imgui.h>

namespace ArcEngine {

	StatusPanel::StatusPanel()
	{
	}

	void StatusPanel::OnImGuiRender()
	{
		ImGui::Begin("Renderer Status");
		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Status:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

	}
}


