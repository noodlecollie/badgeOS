#include "InputDebugScreen.h"
#include "../ScreenDefs.h"
#include "heltec.h"
#include "../../InputEventSystem/InputDefs.h"
#include "../Images/Maple.h"

#define SERIAL_PRINTF(...) Serial.printf("InputDebugScreen: " __VA_ARGS__)

namespace BadgeOS
{
	InputDebugScreen::InputDebugScreen() :
		BaseScreen(Screen::Screen_InputDebug)
	{
		m_InputEventCallback = [this](const Input::Event& event)
		{
			handleInputEvent(event);
		};

		m_UpdateCallback = [this](TimevalMs frameTime) -> Screen::UpdateResponse
		{
			return update(frameTime);
		};

		m_RenderCallback = [this]()
		{
			render();
		};
	}

	void InputDebugScreen::handleInputEvent(const Input::Event& event)
	{
		SERIAL_PRINTF("Received input event %s->%s @ %lu\r\n",
					  Input::deviceName(event.device),
					  Input::actionName(event.action),
					  event.timestamp);

		if ( m_ButtonState != event.action )
		{
			m_ButtonState = event.action;
			m_NeedsRedraw = true;
		}
	}

	Screen::UpdateResponse InputDebugScreen::update(TimevalMs frameTime)
	{
		// For now, just clear the whole screen.
		// There is also support for not clearing the screen so that we can draw on top of
		// certain areas only, but we don't need to make things overly complicated include
		// this debugging class.
		return m_NeedsRedraw ? Screen::UpdateResponse::ClearAndRender : Screen::UpdateResponse::NoRender;
	}

	void InputDebugScreen::render()
	{
		// TODO: Make this not be Maple.
		Heltec.display->drawFastImage(0, 0, Image_Maple::WIDTH, Image_Maple::HEIGHT, Image_Maple::DATA);

		m_NeedsRedraw = false;
	}
}
