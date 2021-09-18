#pragma once

#include "Arc.h"
#include "../Panels/SceneHierarchyPanel.h"

namespace ArcEngine {

	class FileMenu
	{
	public:
		FileMenu() = default;

		void OnImGuiRender();

		void SetActiveScene(const Ref<Scene>& scene)							{ m_ActiveScene = scene; }
		void SetViewportSize(const glm::vec2& viewportSize)						{ m_ViewportSize = viewportSize; }
		void SetSceneHierarchyPanel(SceneHierarchyPanel* sceneHierarchyPanel)	{ m_SceneHierarchyPanel = sceneHierarchyPanel; }

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveSceneAs() const; 

		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		Ref<Scene>					m_ActiveScene;
		glm::vec2					m_ViewportSize;
		SceneHierarchyPanel*		m_SceneHierarchyPanel;
	};

}
