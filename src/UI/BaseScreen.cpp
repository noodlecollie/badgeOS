#include "BaseScreen.h"
#include "../InputEventSystem/InputDefs.h"
#include "../CoreUtil/Assert.h"

namespace BadgeOS
{
	BaseScreen::BaseScreen(Screen::ScreenId id) :
		m_Id(id)
	{
		BOS_ASSERT(id != Screen::ScreenId::Screen_Invalid, "Screen ID was invalid!");
	}

	Screen::ScreenId BaseScreen::id() const
	{
		return m_Id;
	}

	void BaseScreen::handleInputEvent(const Input::Event& event)
	{
		if ( m_InputEventHandler )
		{
			m_InputEventHandler(event);
		}
	}
}
