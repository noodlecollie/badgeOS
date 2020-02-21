#pragma once

#include "../Time/TimeHelpers.h"

namespace BadgeOS
{
	namespace Input
	{
		enum class Device
		{
			None = 0,
			Button0 = (1 << 0)
		};

		enum class Action
		{
			None = 0,
			Released = (1 << 1),
			Pressed = (1 << 2),
			Held = (1 << 3)
		};

		static constexpr TimevalMs BUTTON_HOLD_TIME_MS = 1000;

		struct Event
		{
			Input::Device device;
			Input::Action action;
			TimevalMs timestamp;
		};
	}
}
