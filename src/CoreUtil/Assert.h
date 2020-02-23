#pragma once

namespace BadgeOS
{
	void assertFunc(bool condition, const char* conditionStr, const char* desc, const char* file, int line);
}

#define BOS_ASSERT(cond, desc) ::BadgeOS::assertFunc(cond, #cond, desc, __FILE__, __LINE__)
