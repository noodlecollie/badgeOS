#pragma once

#include <functional>
#include "ScreenDefs.h"
#include "../Time/TimeHelpers.h"

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
		Screen::UpdateResponse update(TimevalMs frameTime);
		void render();

	protected:
		explicit BaseScreen(Screen::ScreenId id);

		Screen::ScreenId m_Id = Screen::Screen_Invalid;
		std::function<void(const Input::Event)> m_InputEventCallback;
		std::function<Screen::UpdateResponse(TimevalMs)> m_UpdateCallback;
		std::function<void()> m_RenderCallback;
	};
}
