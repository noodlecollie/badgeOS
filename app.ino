#include "heltec.h"
#include "src/test/test.h"

volatile bool InterruptState = false;

static void buttonInterrupt()
{
	InterruptState = !InterruptState;
}

void setup()
{
	pinMode(LED,OUTPUT);
	digitalWrite(LED,HIGH);

	pinMode(KEY_BUILTIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(KEY_BUILTIN), buttonInterrupt, CHANGE);

	Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);
}

void loop()
{
	digitalWrite(LED,HIGH);
	Test(InterruptState ? "LED high (*)" : "LED high");
	delay(2000);

	digitalWrite(LED,LOW);
	Test(InterruptState ? "LED low (*)" : "LED low");
	delay(2000);
}
