#pragma once

#include "Arc.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/StatusPanel.h"

#include "Viewports/EditorViewport.h"
#include "Viewports/RuntimeViewport.h"

#include "Menus/FileMenu.h"

#include "Arc/Renderer/EditorCamera.h"




namespace ArcEngine {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void		OnAttach() override;
		virtual void		OnDetach() override;

		virtual void		OnUpdate(Timestep ts) override;
		virtual void		OnImGuiRender() override;
		virtual void		OnEvent(Event& e) override;
	private:
		bool				OnKeyPressed(KeyPressedEvent& e);
		bool				OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void				NewScene();
		void				OpenScene();
		void				OpenScene(const std::filesystem::path& path);
		void				SaveScene();
		void				SaveSceneAs();

		void				SerializeScene(Ref<Scene> scene, const std::filesystem::path& path);


		void				OnScenePlay();
		void				OnSceneStop();

		void				OnDuplicateEntity();

		// UI Panels
		void				UI_Toolbar();

		void				ImGuiInit();
	private:

		struct ProfileResult
		{
			const char*	Name;
			float		Time;
		};

		std::vector<ProfileResult> m_ProfileResults;

		Ref<Framebuffer>			m_Framebuffer;
		Ref<Scene>					m_ActiveScene;
		Ref<Scene>					m_EditorScene;
		std::filesystem::path		m_EditorScenePath;

		Entity						m_HoveredEntity;

		bool						m_eViewportFocused  = true;
		bool						m_ViewportFocused	= false;
		bool						m_ViewportHovered	= false;
		int							m_GizmoType			= -1;

		glm::vec2					m_ViewportSize	= { 0.0f, 0.0f };
		glm::vec2					m_ViewportBounds[2];


		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState					m_SceneState = SceneState::Edit;

		// Panels
		SceneHierarchyPanel			m_SceneHierarchyPanel;
		ContentBrowserPanel			m_ContentBrowserPanel;
		StatusPanel					m_StatusPanel;
		EditorViewport				m_EditorViewport;
		RuntimeViewport				m_RuntimeViewport;

		Entity						m_PrimaryCameraEntity;
		EditorCamera				m_EditorCamera;
		// Menus
		FileMenu					m_FileMenu;

		// Editor resources
		Ref<Texture2D> m_IconPlay, m_IconStop;
	};

}
