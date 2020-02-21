#pragma once

#include "../Time/TimeHelpers.h"

// Max number of devices and actions is 16 of each.
#define INPUT_DEVICE_LIST \
	LIST_ITEM(None = 0, "None") \
	LIST_ITEM(Button0 = (1 << 0), "Button0")

#define INPUT_ACTION_LIST \
	LIST_ITEM(None = 0, "None") \
	LIST_ITEM(Released = (1 << 0), "Released") \
	LIST_ITEM(Pressed = (1 << 1), "Pressed") \
	LIST_ITEM(Held = (1 << 2), "Held")

namespace BadgeOS
{
	namespace Input
	{
#define LIST_ITEM(enumVal, name) enumVal,
		enum class Device
		{
			INPUT_DEVICE_LIST
		};

		enum class Action
		{
			INPUT_ACTION_LIST
		};
#undef LIST_ITEM

		static constexpr TimevalMs BUTTON_HOLD_TIME_MS = 1000;

		struct Event
		{
			Input::Device device = Input::Device::None;
			Input::Action action = Input::Action::None;
			TimevalMs timestamp = 0;
		};

		const char* deviceName(Device device);
		const char* actionName(Action action);
	}
}
