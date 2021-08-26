#include "apch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Arc/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace ArcEngine {

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnUpdateRuntime(Timestep ts)
	{

		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					if (nsc.hasScriptAttached) 
					{
						if (!nsc.Instance)
						{
							nsc.Instance = nsc.InstantiateScript();
							nsc.Instance->m_Entity = Entity{ entity, this };

							nsc.Instance->OnCreate();
						}

						nsc.Instance->OnUpdate(ts);
					}
					
				});
		}


		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
			}

			Renderer2D::EndScene();
		}

	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
		}

		Renderer2D::EndScene();
	}


	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}

	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
		component.ScriptName = "No Script attached";
		component.hasScriptAttached = false;
	}

	void Scene::OnEvent(Event& e)
	{
		//if (Input::IsKeyPressed(Key::Escape) && m_IsPlaying == true)
		{
			OnRuntimeStop();
			ARC_CORE_INFO("Runtime stopped by pressing escape!");
		}
	}

	void Scene::OnRuntimeStart()
	{
		//Do physics and other runtime stuff (TODO)
		//m_IsPlaying = true;
	}

	void Scene::OnRuntimeStop()
	{
		//Input::SetCursorMode(MousePointerMode::Normal);
		//Cleanup physics stuff (TODO)
		//m_IsPlaying = false;
	}


	void Scene::ClearRegistry()
	{
		m_Registry.clear();
	}

	template<typename T>
	static void CopyComponent(entt::registry& dstRegistry, entt::registry& srcRegistry, const std::unordered_map<UUID, entt::entity>& enttMap)
	{
		auto components = srcRegistry.view<T>();
		for (auto srcEntity : components)
		{
			entt::entity destEntity = enttMap.at(srcRegistry.get<IDComponent>(srcEntity).ID);

			auto& srcComponent = srcRegistry.get<T>(srcEntity);
			auto& destComponent = dstRegistry.emplace_or_replace<T>(destEntity, srcComponent);
		}
	}

	//Entity Scene::CreateEntityWithID(UUID uuid, const std::string& name, bool runtimeMap)
	//{
	//	auto entity = Entity{ m_Registry.create(), this };
	//	auto& idComponent = entity.AddComponent<IDComponent>();
	//	idComponent.ID = uuid;

	//	entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
	//	if (!name.empty())
	//		entity.AddComponent<TagComponent>(name);

	//	ARC_CORE_ASSERT(m_EntityIDMap.find(uuid) == m_EntityIDMap.end());
	//	//m_EntityIDMap[uuid] = entity;
	//	return entity;
	//}




	//void Scene::CopySceneTo(Ref<Scene>& target)
	//{
	//	std::unordered_map<UUID, entt::entity> enttMap;
	//	auto idComponents = m_Registry.view<IDComponent>();
	//	for (auto entity : idComponents)
	//	{
	//		auto uuid = m_Registry.get<IDComponent>(entity).ID;
	//		Entity e = target->CreateEntityWithID(uuid, "", true);
	//	
	//	}

	//	CopyComponent<TagComponent>(target->m_Registry, m_Registry, enttMap);
	//	CopyComponent<TransformComponent>(target->m_Registry, m_Registry, enttMap);
	//	CopyComponent<CameraComponent>(target->m_Registry, m_Registry, enttMap);
	//	CopyComponent<SpriteRendererComponent>(target->m_Registry, m_Registry, enttMap);
	//}



}
