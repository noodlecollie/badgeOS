#include "Board.h"
#include "heltec.h"

namespace BadgeOS
{
	namespace HeltecESP32WifiKit32
	{
		// Most of these helper functions were taken from the Heltec library begin() function,
		// and modified so as not to include the unnecessary Chinese-English log messages.
		static inline void initialiseSerial()
		{
			// TODO: Make baud rate configurable one day?
			Serial.begin(115200);
			Serial.flush();
		}

		static inline void initialiseOLED()
		{
			// TODO: Make font configurable one day?
			Heltec.display->init();
			Heltec.display->flipScreenVertically();
			Heltec.display->setFont(ArialMT_Plain_10);
			Heltec.display->clear();
		}

		void initialiseHardware()
		{
			pinMode(LED, OUTPUT);
			digitalWrite(LED, LOW);

			pinMode(KEY_BUILTIN, INPUT_PULLUP);
			digitalWrite(KEY_BUILTIN, LOW);

			initialiseSerial();
			initialiseOLED();

			Serial.println("*** Hardware board initialised. ***");
		}
	}
}
