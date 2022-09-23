#pragma once

#include "Arc/Core/KeyCodes.h"
#include "Arc/Core/MouseCodes.h"

#include <glm/glm.hpp>


namespace ArcEngine {

	class Input
	{
	// Singleton pattern
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
