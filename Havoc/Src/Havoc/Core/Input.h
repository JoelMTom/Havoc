#pragma once

#include "Havoc/Core/KeyCodes.h"
#include "Havoc/Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Havoc
{
	class Input
	{
	public:
		static bool IsKeyPressed(const KeyCode key);

		static bool IsMouseButtonPressed(const MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}