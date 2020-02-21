#include "ScreenContainer.h"
#include "BaseScreen.h"
#include "../InputEventSystem/InputDefs.h"

namespace BadgeOS
{
	bool ScreenContainer::addScreen(BaseScreen* screen)
	{
		if ( !screen || m_ScreenCount >= MAX_SCREENS )
		{
			return false;
		}

		for ( uint32_t index = 0; index < MAX_SCREENS; ++index )
		{
			if ( !m_Screens[index] )
			{
				m_Screens[index] = screen;
				++m_ScreenCount;

				return true;
			}
		}

		return false;
	}

	bool ScreenContainer::setCurrentScreen(Screen::ScreenId id)
	{
		if ( id == Screen::Screen_Invalid )
		{
			return false;
		}

		for ( uint32_t index = 0; index < MAX_SCREENS; ++index )
		{
			if ( m_Screens[index] && m_Screens[index]->id() == id )
			{
				m_CurrentScreen = m_Screens[index];
				return true;
			}
		}

		return false;
	}

	void ScreenContainer::clearCurrentScreen()
	{
		m_CurrentScreen = nullptr;
	}

	void ScreenContainer::handleInputEvent(const Input::Event& event)
	{
		if ( !m_CurrentScreen )
		{
			return;
		}

		m_CurrentScreen->handleInputEvent(event);
	}
}
