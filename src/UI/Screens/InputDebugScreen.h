#pragma once

#include "../BaseScreen.h"

namespace BadgeOS
{
	class InputDebugScreen : public BaseScreen
	{
	public:
		InputDebugScreen();

	private:
		void handleInputEvent(const Input::Event& event);
	};
}
