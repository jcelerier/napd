#pragma once
#include "Checkable.h"
#include <QString>

struct Unit : public Checkable
{
		Unit(QString&& n, uint32_t t):
			Checkable{t},
			name{n}
		{
		}
		
		const QString name;
};