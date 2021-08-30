#pragma once

#include "Arc/Script/ScriptEngine.h"
#include "Arc/Core/KeyCodes.h"

#include <glm/glm.hpp>

extern "C" {
	typedef struct _MonoString MonoString;
	typedef struct _MonoArray MonoArray;
}

namespace ArcEngine {

	namespace Script {

		// Input
		bool Arc_Input_IsKeyPressed(KeyCode key);

		// Entity
		void Arc_Entity_GetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* outTransform);
		void Arc_Entity_SetTransform(uint32_t sceneID, uint32_t entityID, glm::mat4* inTransform);
		void Arc_Entity_CreateComponent(uint32_t sceneID, uint32_t entityID, void* type);
		bool Arc_Entity_HasComponent(uint32_t sceneID, uint32_t entityID, void* type);

		// Renderer
		// Texture2D
		void* Arc_Texture2D_Constructor(uint32_t width, uint32_t height);
		void Arc_Texture2D_Destructor(Ref<Texture2D>* _this);
		void Arc_Texture2D_SetData(Ref<Texture2D>* _this, MonoArray* inData, int32_t count);


	}
}
