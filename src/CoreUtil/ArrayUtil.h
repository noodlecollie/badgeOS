#pragma once

#include <cstddef>

namespace BadgeOS
{
	namespace ArrayUtil
	{
		template<size_t SIZE, typename T>
		static inline constexpr size_t arraySize(T(&arr)[SIZE])
		{
			return SIZE;
		}
	}
}
