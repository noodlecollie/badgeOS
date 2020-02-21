#include "InputDefs.h"
#include "../CoreUtil/ArrayUtil.h"

namespace BadgeOS
{
	namespace Input
	{
#define LIST_ITEM(enumVal, name) name,
		static const char* const DeviceNames[] =
		{
			INPUT_DEVICE_LIST
		};

		static const char* const ActionNames[] =
		{
			INPUT_ACTION_LIST
		};
#undef LIST_ITEM

		static inline const char* findName(const char* const* namesArray, size_t namesArrayLength, uint32_t searchFlag)
		{
			for ( uint32_t index = 0; index < namesArrayLength; ++index )
			{
				const uint32_t indexAsFlag = index > 0 ? (1 << (index - 1)) : 0;

				if ( indexAsFlag == searchFlag )
				{
					return namesArray[index];
				}
			}

			return "UNKNOWN";
		}

		const char* deviceName(Device device)
		{
			return findName(DeviceNames, ArrayUtil::arraySize(DeviceNames), static_cast<uint32_t>(device));
		}

		const char* actionName(Action action)
		{
			return findName(ActionNames, ArrayUtil::arraySize(ActionNames), static_cast<uint32_t>(action));
		}
	}
}
