#pragma once

#include "Arc.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/StatusPanel.h"

#include "Viewports/EditorViewport.h"

#include "Menus/FileMenu.h"

#include "Arc/Renderer/EditorCamera.h"




namespace ArcEngine {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void ImGuiInit();
	private:

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult> m_ProfileResults;
		Ref<Framebuffer> m_Framebuffer;


		Ref<Scene> m_ActiveScene;
		Entity m_HoveredEntity;

		EditorCamera m_EditorCamera;
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		ContentBrowserPanel m_ContentBrowserPanel;
		StatusPanel m_StatusPanel;
		EditorViewport m_EditorViewport;

		FileMenu m_FileMenu;
		// Menus
	};

}
