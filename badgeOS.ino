#include "heltec.h"
#include "TimeAlarms.h"
#include "src/InputEventSystem/Interrupts.h"
#include "src/InputEventSystem/InputEventSystem.h"
#include "src/Board/HeltecESP32WifiKit32/Board.h"

void setup()
{
	BadgeOS::HeltecESP32WifiKit32::initialiseHardware();
	BadgeOS::InputInterrupts::initialise();

	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
}

void loop()
{
	using namespace BadgeOS;

	InputInterrupts::update();
	InputEventSystem::staticInstance().update();

	Heltec.display->clear();

	if ( InputInterrupts::hasNewInputEvent() )
	{
		const char* deviceName = "UNKNOWN";
		const char* actionName = "UNKNOWN";

		switch ( InputInterrupts::inputDevice() )
		{
			case Input::Device::Button0:
			{
				deviceName = "Button0";
				break;
			}

			default:
			{
				break;
			}
		}

		switch ( InputInterrupts::inputAction() )
		{
			case Input::Action::Pressed:
			{
				actionName = "Pressed";
				break;
			}

			case Input::Action::Released:
			{
				actionName = "Released";
				break;
			}

			default:
			{
				break;
			}
		}

		String output;
		output += "Input received: ";
		output += deviceName;
		output += " in state ";
		output += actionName;
		output += ".";

		Heltec.display->drawStringMaxWidth(0, 0, 128, output);
		digitalWrite(LED, HIGH);
	}
	else
	{
		Heltec.display->drawString(0, 0, "No inputs detected.");
		digitalWrite(LED, LOW);
	}

	Heltec.display->display();
	Alarm.delay(1000/25);
}
