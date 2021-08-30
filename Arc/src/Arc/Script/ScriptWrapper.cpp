#include "apch.h"
#include "ScriptWrapper.h"

#include "Arc/Scene/Scene.h"
#include "Arc/Scene/Entity.h"
#include "Arc/Scene/Components.h"

#include <glm/gtc/type_ptr.hpp>

#include "Arc/Core/Input.h"
#include <mono/jit/jit.h>

namespace ArcEngine {

	extern std::unordered_map<uint32_t, Scene*> s_ActiveScenes;
	extern std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	extern std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;


	namespace Script {

		enum class ComponentID
		{
			None = 0,
			Transform = 1,
			Mesh = 2,
			Script = 3,
			SpriteRenderer = 4
		};

		////////////////////////////////////////////////////////////////
		// Input ///////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		bool Arc_Input_IsKeyPressed(KeyCode key)
		{
			return Input::IsKeyPressed(key);
		}

		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		// Entity //////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////

		void Arc_Entity_GetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* outTransform)
		{
			ARC_CORE_ASSERT(s_ActiveScenes.find(sceneID) != s_ActiveScenes.end(), "Invalid Scene ID!");

			Scene* scene = s_ActiveScenes[sceneID];
			Entity entity((entt::entity)entityID, scene);
			auto& transformComponent = entity.GetComponent<TransformComponent>();
			memcpy(outTransform, glm::value_ptr(transformComponent.GetTransform()), sizeof(glm::mat4));
		}

		void Arc_Entity_SetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* inTransform)
		{
			ARC_CORE_ASSERT(s_ActiveScenes.find(sceneID) != s_ActiveScenes.end(), "Invalid Scene ID!");

			Scene* scene = s_ActiveScenes[sceneID];
			Entity entity((entt::entity)entityID, scene);
			auto& transformComponent = entity.GetComponent<TransformComponent>();
			memcpy(glm::value_ptr(transformComponent.GetTransform()), inTransform, sizeof(glm::mat4));
		}

		void Arc_Entity_CreateComponent(uint32_t sceneID, uint32_t entityID, void* type)
		{
			ARC_CORE_ASSERT(s_ActiveScenes.find(sceneID) != s_ActiveScenes.end(), "Invalid Scene ID!");
			MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);

			Scene* scene = s_ActiveScenes[sceneID];
			Entity entity((entt::entity)entityID, scene);
			s_CreateComponentFuncs[monoType](entity);
		}

		bool Arc_Entity_HasComponent(uint32_t sceneID, uint32_t entityID, void* type)
		{
			ARC_CORE_ASSERT(s_ActiveScenes.find(sceneID) != s_ActiveScenes.end(), "Invalid Scene ID!");
			MonoType* monoType = mono_reflection_type_get_type((MonoReflectionType*)type);

			Scene* scene = s_ActiveScenes[sceneID];
			Entity entity((entt::entity)entityID, scene);
			bool result = s_HasComponentFuncs[monoType](entity);
			return result;
		}

		void* Arc_Texture2D_Constructor(uint32_t width, uint32_t height)
		{
			auto result = Texture2D::Create(TextureFormat::RGBA, width, height);
			return new Ref<Texture2D>(result);
		}

		void Arc_Texture2D_Destructor(Ref<Texture2D>* _this)
		{
			delete _this;
		}

		void Arc_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count)
		{
			// TODO

			//Ref<Texture2D>& instance = *_this;

			//uint32_t dataSize = count * sizeof(glm::vec4) / 4;

			//instance->Lock();
			//Buffer buffer = instance->GetWriteableBuffer();
			//ARC_CORE_ASSERT(dataSize <= buffer.Size);
			//// Convert RGBA32F color to RGBA8
			//uint8_t* pixels = (uint8_t*)buffer.Data;
			//uint32_t index = 0;
			//for (int i = 0; i < instance->GetWidth() * instance->GetHeight(); i++)
			//{
			//	glm::vec4& value = mono_array_get(inData, glm::vec4, i);
			//	*pixels++ = (uint32_t)(value.x * 255.0f);
			//	*pixels++ = (uint32_t)(value.y * 255.0f);
			//	*pixels++ = (uint32_t)(value.z * 255.0f);
			//	*pixels++ = (uint32_t)(value.w * 255.0f);
			//}

			//instance->Unlock();
		}

	}
}
