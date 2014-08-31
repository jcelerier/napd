#pragma once
#include "Checkable.h"
#include <QString>

template<typename T>
struct Facultative
{
	bool isSet{};
	T val;
	
	const T& operator()() const
	{
		return val;
	}
	
	void set(const T& t)
	{
		isSet = true;
		val = t;
	}
};

using FacultativeString = Facultative<QString>;

struct Process : public Checkable
{
		Process(uint32_t t):
			Checkable{t}
		{
		}
		
		FacultativeString path;
		FacultativeString basename;
		FacultativeString cmdline;
};