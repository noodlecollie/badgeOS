#pragma once

#include "../BaseScreen.h"
#include "../../CoreUtil/Singleton.h"
#include "../../InputEventSystem/InputDefs.h"

namespace BadgeOS
{
	class InputDebugScreen : public BaseScreen, public Singleton<InputDebugScreen>
	{
	public:
		InputDebugScreen();

	private:
		void handleInputEvent(const Input::Event& event);
		Screen::UpdateResponse update(TimevalMs frameTime);
		void render();

		Input::Action m_ButtonState = Input::Action::None;
		bool m_NeedsRedraw = true;
	};
}
