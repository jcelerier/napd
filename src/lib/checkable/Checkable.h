#pragma once
#include <cinttypes>

struct Checkable
{
		Checkable(uint32_t t):
			timeout{t}
		{
		}

		const uint32_t timeout; // in seconds
};
