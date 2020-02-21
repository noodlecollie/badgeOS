#include "Board.h"
#include "heltec.h"

namespace BadgeOS
{
	namespace HeltecESP32WifiKit32
	{
		void initialiseHardware()
		{
			pinMode(LED, OUTPUT);
			digitalWrite(LED, LOW);

			pinMode(KEY_BUILTIN, INPUT_PULLUP);
			digitalWrite(KEY_BUILTIN, LOW);
		}
	}
}
