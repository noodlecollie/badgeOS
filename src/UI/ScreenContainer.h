#pragma once

#include <cstddef>
#include <cstdint>

#include "../CoreUtil/Singleton.h"
#include "ScreenDefs.h"
#include "../Time/TimeHelpers.h"

namespace BadgeOS
{
	namespace Input
	{
		struct Event;
	}

	class BaseScreen;

	class ScreenContainer : public Singleton<ScreenContainer>
	{
	public:
		static constexpr size_t MAX_SCREENS = 16;

		bool addScreen(BaseScreen* screen);
		bool setCurrentScreen(Screen::ScreenId id);
		void clearCurrentScreen();

		void handleInputEvent(const Input::Event& event);
		Screen::UpdateResponse update(TimevalMs frameTime);
		void render();

	private:
		BaseScreen* m_Screens[MAX_SCREENS];
		size_t m_ScreenCount = 0;
		BaseScreen* m_CurrentScreen = nullptr;
		Screen::UpdateResponse m_LastUpdateResponse = Screen::UpdateResponse::NoRender;
	};
}
