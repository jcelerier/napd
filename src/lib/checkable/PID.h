#pragma once
#include "Checkable.h"
#include <algorithm>
struct PID : public Checkable
{
		PID(uint32_t p, uint32_t t):
			Checkable{t},
			pid{p}
		{
			
		}
		
		PID(PID&&) = default;
		PID(const PID&) = default;
		PID& operator=(const PID&) = default;
		PID& operator=(PID&& e) { pid = e.pid; return *this; }
		
		bool operator==(unsigned int elt)
		{
			return pid == elt;
		}

		uint32_t pid;
};
