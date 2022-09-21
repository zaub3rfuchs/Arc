#pragma once

#include "Arc/Core/Core.h"
#include "Arc/Scene/Scene.h"
#include "Arc/Scene/Entity.h"

namespace ArcEngine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void		SetContext(const Ref<Scene>& scene);

		void		OnImGuiRender();

		void		SetSelectedEntity(Entity entity)			{ m_SelectionContext = entity; }
		Entity		GetSelectedEntity() const					{ return m_SelectionContext; }

	private:
		template<typename T>
		void DisplayAddComponentEntry(const std::string& entryName);

		void		DrawEntityNode(Entity entity);
		void		DrawComponents(Entity entity);
		void		DrawAddComponent(Entity entity);
	private:
		Ref<Scene>	m_Context;
		Entity		m_SelectionContext;
	};

}
