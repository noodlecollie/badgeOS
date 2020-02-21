#pragma once

#include <functional>
#include "ScreenDefs.h"

namespace BadgeOS
{
	namespace Input
	{
		struct Event;
	}

	class BaseScreen
	{
	public:
		Screen::ScreenId id() const;

		void handleInputEvent(const Input::Event& event);

	protected:
		explicit BaseScreen(Screen::ScreenId id);

		Screen::ScreenId m_Id = Screen::Screen_Invalid;
		std::function<void(const Input::Event)> m_InputEventHandler;
	};
}
