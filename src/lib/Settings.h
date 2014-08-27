#pragma once

#include "CheckedProcesses.h"
#include "CustomChecks.h"
#include "CheckedUnits.h"

#include <cinttypes>

struct Settings
{
	CheckedProcesses checkedProcesses;
	CheckedUnits checkedUnits;
	CustomChecks customChecks;
	
	uint32_t defaultTimeout{60};
	
	// Custom checks
	std::string defaultUser{"root"};
	int defaultReturnCode{};
};
