#ifndef SETTINGS_H
#define SETTINGS_H

#include "CheckedProcesses.h"
#include "CustomChecks.h"
#include "CheckedUnits.h"
struct Settings
{
	CheckedProcesses checkedProcesses;
	CheckedUnits checkedUnits;
	CustomChecks customChecks;
};

#endif // SETTINGS_H
