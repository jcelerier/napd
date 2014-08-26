#pragma once
#include "Checkable.h"
#include <string>

struct Process : public Checkable
{
		Process(std::string n, int t):
			Checkable(t),
			name(n)
		{
		}
		
		std::string name;
};