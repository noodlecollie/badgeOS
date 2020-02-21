#pragma once

#include <functional>
#include "InputDefs.h"
#include "../Time/TimeHelpers.h"
#include "../CoreUtil/Singleton.h"

namespace BadgeOS
{
	class InputEventSystem : public Singleton<InputEventSystem>
	{
	public:
		using EventHandler = std::function<void(const Input::Event& event)>;

		void setEventHandler(EventHandler handler);
		void update();

	private:
		bool createNextEvent();

		EventHandler m_EventHandler;
		Input::Event m_CurrentEvent;
	};
}
