#pragma once

#include <cstdint>
#include "InputDefs.h"

namespace BadgeOS
{
	namespace InputInterrupts
	{
		void initialise();

		// Call this to update the working copy of the data from the
		// volatile interrupt copy, before calling the functions below.
		void update();

		bool hasNewInputEvent();
		Input::Device inputDevice();
		Input::Action inputAction();
	}
}
