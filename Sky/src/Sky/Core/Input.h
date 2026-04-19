#pragma once

#include "Sky/Core/KeyCodes.h"

namespace Sky {

	class Input 
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}
