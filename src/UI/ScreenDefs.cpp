#include "ScreenDefs.h"
#include "ScreenContainer.h"
#include "Screens/InputDebugScreen.h"

namespace BadgeOS
{
	namespace Screen
	{
		void initialiseScreens()
		{
			ScreenContainer& container = ScreenContainer::staticInstance();

			container.addScreen(&InputDebugScreen::staticInstance());
		}
	}
}
