#include "InputDebugScreen.h"
#include "../ScreenIds.h"
#include "heltec.h"
#include "../../InputEventSystem/InputDefs.h"

namespace BadgeOS
{
	InputDebugScreen::InputDebugScreen() :
		BaseScreen(Screen::Screen_InputDebug)
	{
		m_InputEventHandler = [this](const Input::Event& event)
		{
			handleInputEvent(event);
		};
	}

	void InputDebugScreen::handleInputEvent(const Input::Event& event)
	{
		Serial.printf("Received input event: %x, %x, %lx\n", (uint32_t)event.device, (uint32_t)event.action, event.timestamp);
	}
}
