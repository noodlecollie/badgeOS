#include "InputDebugScreen.h"
#include "../ScreenDefs.h"
#include "heltec.h"
#include "../../InputEventSystem/InputDefs.h"

#define SERIAL_PRINTF(...) Serial.printf("InputDebugScreen: " __VA_ARGS__)

namespace BadgeOS
{
	InputDebugScreen::InputDebugScreen() :
		BaseScreen(Screen::/*Screen_InputDebug*/Screen_Invalid)
	{
		m_InputEventCallback = [this](const Input::Event& event)
		{
			handleInputEvent(event);
		};
	}

	void InputDebugScreen::handleInputEvent(const Input::Event& event)
	{
		SERIAL_PRINTF("Received input event %s->%s @ %lu\r\n",
					  Input::deviceName(event.device),
					  Input::actionName(event.action),
					  event.timestamp);
	}
}
