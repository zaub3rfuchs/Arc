#include "apch.h"
#include "ScriptEngineRegistry.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Arc/Scene/Entity.h"
#include "ScriptWrapper.h"
#include <iostream>

namespace ArcEngine {

	std::unordered_map<MonoType*, std::function<bool(Entity&)>> s_HasComponentFuncs;
	std::unordered_map<MonoType*, std::function<void(Entity&)>> s_CreateComponentFuncs;

	extern MonoImage* s_CoreAssemblyImage;

#define Component_RegisterType(Type) \
	{\
		MonoType* type = mono_reflection_type_from_name("Arc." #Type, s_CoreAssemblyImage);\
		if (type) {\
			uint32_t id = mono_type_get_type(type);\
			s_HasComponentFuncs[type] = [](Entity& entity) { return entity.HasComponent<Type>(); };\
			s_CreateComponentFuncs[type] = [](Entity& entity) { entity.AddComponent<Type>(); };\
		} else {\
			ARC_CORE_ERROR("No C# component class found for " #Type "!");\
		}\
	}

	static void InitComponentTypes()
	{
		Component_RegisterType(TagComponent);
		Component_RegisterType(TransformComponent);
		Component_RegisterType(ScriptComponent);
		Component_RegisterType(CameraComponent);
		Component_RegisterType(SpriteRendererComponent);
	}

	void ScriptEngineRegistry::RegisterAll()
	{
		InitComponentTypes();


		mono_add_internal_call("Hazel.Entity::GetTransform_Native", ArcEngine::Script::Arc_Entity_GetTransform);
		mono_add_internal_call("Hazel.Entity::SetTransform_Native", ArcEngine::Script::Arc_Entity_SetTransform);
		mono_add_internal_call("Hazel.Entity::CreateComponent_Native", ArcEngine::Script::Arc_Entity_CreateComponent);
		mono_add_internal_call("Hazel.Entity::HasComponent_Native", ArcEngine::Script::Arc_Entity_HasComponent);

		mono_add_internal_call("Hazel.Input::IsKeyPressed_Native", ArcEngine::Script::Arc_Input_IsKeyPressed);

		mono_add_internal_call("Hazel.Texture2D::Constructor_Native", ArcEngine::Script::Arc_Texture2D_Constructor);
		mono_add_internal_call("Hazel.Texture2D::Destructor_Native", ArcEngine::Script::Arc_Texture2D_Destructor);
		mono_add_internal_call("Hazel.Texture2D::SetData_Native", ArcEngine::Script::Arc_Texture2D_SetData);



		// static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
		// 
		// static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		// static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		// static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		// static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	}

}
