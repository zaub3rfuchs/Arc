#pragma once

#include "Arc/Core/Timestep.h"
#include "Arc/Renderer/EditorCamera.h"
#include "Arc/Core/UUID.h"
#include "entt.hpp"

namespace ArcEngine {

	class Entity;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);

		void OnEvent(Event& e);

		void OnRuntimeStart();
		void OnUpdateRuntime(Timestep ts);
		void OnRuntimeStop();

		void ClearRegistry();

		Entity CreateEntityWithID(UUID uuid, const std::string& name, bool runtimeMap);
		void CopySceneTo(Ref<Scene>& target);

		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}
