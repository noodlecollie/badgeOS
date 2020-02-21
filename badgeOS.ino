#include "heltec.h"
#include "TimeAlarms.h"
#include "src/InputEventSystem/Interrupts.h"
#include "src/InputEventSystem/InputEventSystem.h"
#include "src/Board/HeltecESP32WifiKit32/Board.h"
#include "src/UI/ScreenContainer.h"
#include "src/UI/ScreenDefs.h"

void setup()
{
	using namespace BadgeOS;

	HeltecESP32WifiKit32::initialiseHardware();
	InputInterrupts::initialise();
	Screen::initialiseScreens();

	InputEventSystem::staticInstance().setEventHandler([](const Input::Event& event)
	{
		ScreenContainer::staticInstance().handleInputEvent(event);
	});

	ScreenContainer::staticInstance().setCurrentScreen(Screen::Screen_InputDebug);
}

void loop()
{
	using namespace BadgeOS;

	InputInterrupts::update();
	InputEventSystem::staticInstance().update();

	Alarm.delay(1000/25);
}
