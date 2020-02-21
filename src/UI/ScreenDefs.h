#pragma once

namespace BadgeOS
{
	namespace Screen
	{
		enum ScreenId
		{
			Screen_InputDebug = 0,

			Screen_Count,
			Screen_Invalid = -1
		};

		enum class UpdateResponse
		{
			NoRender,
			Render,
			ClearAndRender
		};

		void initialiseScreens();
	}
}
