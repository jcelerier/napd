#pragma once
#include <exception>
#include <cinttypes>

class NotReady : public std::exception
{
	public:
		NotReady(uint32_t t):
			std::exception{},
			timeout{t}
		{
		}
		
		uint32_t timeout{};
};