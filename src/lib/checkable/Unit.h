#pragma once
#include "Checkable.h"
#include <string>

struct Unit : public Checkable
{
		Unit(std::string n, int t):
			Checkable(t),
			name(n)
		{
		}
		
		std::string name;
};