#pragma once

#include "CheckedProcesses.h"
#include "CustomChecks.h"
#include "CheckedUnits.h"

#include <cinttypes>
#include <memory>

struct Settings
{
		Settings();
		
		
		std::vector<std::unique_ptr<CheckableCollectionInterface>> checks;
		
		// Default data
		uint32_t defaultTimeout{60};
		
		// Custom checks
		std::string defaultUser{};
		int defaultReturnCode{};
};
