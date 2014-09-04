#pragma once
#include <cinttypes>

struct Checkable
{
		Checkable(uint32_t t):
			timeout{t}
		{
		}
		
		Checkable(const Checkable&) = default;
		Checkable(Checkable&&) = default;
		Checkable& operator=(Checkable&&) = default;

		const uint32_t timeout; // in seconds
};
