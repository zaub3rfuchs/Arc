#pragma once

#include "Arc.h"
#include "../Panels/SceneHierarchyPanel.h"

namespace ArcEngine {

	class FileMenu
	{
	public:
		FileMenu() = default;

		void OnImGuiRender();

		void setActiveScene(const Ref<Scene>& scene) { m_ActiveScene = scene; };
		void setViewportSize(const glm::vec2& viewportSize) { m_ViewportSize = viewportSize; };
		void setSceneHierarchyPanel(SceneHierarchyPanel* sceneHierarchyPanel) { m_SceneHierarchyPanel = sceneHierarchyPanel; };

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs();

		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		Ref<Scene> m_ActiveScene;
		glm::vec2 m_ViewportSize;
		SceneHierarchyPanel* m_SceneHierarchyPanel;
	};

}
