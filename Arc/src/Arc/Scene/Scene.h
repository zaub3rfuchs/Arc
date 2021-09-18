#pragma once

#include "Arc/Core/Timestep.h"
#include "Arc/Renderer/EditorCamera.h"
#include "Arc/Core/UUID.h"
#include "entt.hpp"

class b2World;

namespace ArcEngine {

	class Entity;

	class Scene : public RefCounted
	{
	public:
		Scene();
		~Scene();

		void	DestroyEntity(Entity entity);

		void	OnUpdateEditor(Timestep ts, EditorCamera& camera);
		void	OnViewportResize(uint32_t width, uint32_t height);

		void	OnEvent(Event& e);

		void	OnRuntimeStart();
		void	OnRuntimeStop();

		void	OnUpdateRuntime(Timestep ts);

		void	ClearRegistry();

		void	CopySceneTo(Ref<Scene>& target);

		Entity	CreateEntityWithID(UUID uuid, const std::string& name, bool runtimeMap);
		Entity	CreateEntity(const std::string& name = std::string());
		Entity	GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		UUID m_SceneID;
		entt::registry	m_Registry;
		uint32_t		m_ViewportWidth = 0, m_ViewportHeight = 0;

		std::unordered_map<UUID, Entity> m_EntityIDMap;

		entt::entity m_SceneEntity;

		b2World* m_Box2DWorld = nullptr;

		friend class	Entity;
		friend class	SceneSerializer;
		friend class	SceneHierarchyPanel;
	};

}
