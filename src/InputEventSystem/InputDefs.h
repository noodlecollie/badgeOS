#pragma once

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
			Pressed = (1 << 2)
		};
	}
}
