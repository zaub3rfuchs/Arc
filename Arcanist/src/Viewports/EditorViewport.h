#pragma once

#include "Arc/Renderer/EditorCamera.h"
#include "Arc.h"
#include "../Panels/SceneHierarchyPanel.h"

namespace ArcEngine {

	class EditorViewport
	{
	public:
		EditorViewport() = default;

		void OnImGuiRender();

		const glm::vec2&	getViewPortSize()		{ return m_ViewportSize; };
		const auto			getViewPortBounds()		{ return m_ViewportBounds; };
		const bool&			isViewportHovered()		{ return m_ViewportHovered; };
		const bool&			isViewportFocused()		{ return m_ViewportFocused; };

		void setEditorView(const uint64_t& viewTexture)								{ m_ViewTexture = viewTexture; };
		void setSceneHierarchyPanel(const SceneHierarchyPanel& sceneHierarchyPanel)	{ m_SceneHierarchyPanel = sceneHierarchyPanel; };
	private:
		Ref<Framebuffer>	m_Framebuffer;
		Ref<Scene>			m_ActiveScene;

		SceneHierarchyPanel m_SceneHierarchyPanel;

		bool		m_ViewportFocused	= false;
		bool		m_ViewportHovered	= false;
		glm::vec2	m_ViewportSize		= { 0.0f, 0.0f };
		glm::vec2	m_ViewportBounds[2];

		int			m_GizmoType			= -1;
		uint64_t	m_ViewTexture;
	};

}
