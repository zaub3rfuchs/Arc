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

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity	CreateEntity(const std::string& name = std::string());
		Entity	CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void	DestroyEntity(Entity entity);

		void	OnViewportResize(uint32_t width, uint32_t height);

		void	OnEvent(Event& e);

		void	OnRuntimeStart();
		void	OnRuntimeStop();

		void	OnSimulationStart();
		void	OnSimulationStop();

		void	OnUpdateRuntime(Timestep ts);
		void	OnUpdateSimulation(Timestep ts, EditorCamera& camera);
		void	OnUpdateEditor(Timestep ts, EditorCamera& camera);

		void	DuplicateEntity(Entity entity);

		Entity	GetPrimaryCameraEntity();

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}

		void OnPhysics2DStart();
		void OnPhysics2DStop();

		void RenderScene(EditorCamera& camera);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry	m_Registry;
		uint32_t		m_ViewportWidth = 0, m_ViewportHeight = 0;

		entt::entity m_SceneEntity;

		b2World* m_PhysicsWorld = nullptr;

		friend class	Entity;
		friend class	SceneSerializer;
		friend class	SceneHierarchyPanel;
	};

}
