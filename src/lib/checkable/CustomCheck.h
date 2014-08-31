#pragma once
#include "Checkable.h"
#include <QString>

struct CustomCheck: public Checkable
{
	CustomCheck(QString&& e, 
				QString&& u,
				int eq,
				uint32_t t):
		Checkable{t},
		exec{e},
		user{u},
		mustEqual{eq}
	{
		
	}
	
	const QString exec;
	const QString user;
	const int mustEqual{};
};