#include "FileMenu.h"
#include "Arc/Utils/PlatformUtils.h"
#include "Arc/Scene/SceneSerializer.h"
#include <imgui/imgui.h>
#include "../EditorLayer.h";

namespace ArcEngine {


	void FileMenu::OnImGuiRender()
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();

				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

	}

	void FileMenu::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void FileMenu::OpenScene()
	{
		std::optional<std::string> filepath = FileDialogs::OpenFile("Arc Scene (*.arc)\0*.arc\0");
		if (filepath)
		{
			OpenScene(*filepath);
		}
	}

	void FileMenu::OpenScene(const std::filesystem::path& path)
	{
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		SceneSerializer serializer(m_ActiveScene);
		serializer.Deserialize(path.string());
	}

	void FileMenu::SaveSceneAs()
	{
		std::optional<std::string> filepath = FileDialogs::SaveFile("Arc Scene (*.arc)\0*.arc\0");
		if (filepath)
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(*filepath);
		}
	}


}


