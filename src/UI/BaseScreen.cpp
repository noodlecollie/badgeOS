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
		if ( m_InputEventCallback )
		{
			m_InputEventCallback(event);
		}
	}

	Screen::UpdateResponse BaseScreen::update(TimevalMs frameTime)
	{
		if ( m_UpdateCallback )
		{
			return m_UpdateCallback(frameTime);
		}

		return Screen::UpdateResponse::NoRender;
	}

	void BaseScreen::render()
	{
		if ( m_RenderCallback )
		{
			m_RenderCallback();
		}
	}
}
