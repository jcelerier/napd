#pragma once
#include "Checkable.h"
#include <string>

struct CustomCheck: public Checkable
{
	CustomCheck(std::string e, 
				std::string u,
				int eq,
				int t):
		Checkable(t),
		exec(e),
		user(u),
		mustEqual(eq)
	{
		
	}
	
	std::string exec;
	std::string user;
	int mustEqual{0};
};