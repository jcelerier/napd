#pragma once
#include <exception>

class NotReady : public std::exception
{
	public:
		NotReady(int t):
			std::exception(),
			timeout(t)
		{
		}
		
		int timeout{};
};