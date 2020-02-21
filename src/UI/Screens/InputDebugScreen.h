#pragma once

#include "../BaseScreen.h"
#include "../../CoreUtil/Singleton.h"

namespace BadgeOS
{
	class InputDebugScreen : public BaseScreen, public Singleton<InputDebugScreen>
	{
	public:
		InputDebugScreen();

	private:
		void handleInputEvent(const Input::Event& event);
	};
}
