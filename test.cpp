#include "test.h"
#include "heltec.h"

void Test(const char* string)
{
	Heltec.display -> clear();
	Heltec.display -> drawString(0, 0, string);
	Heltec.display -> display();
}
