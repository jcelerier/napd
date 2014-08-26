#pragma once
#include "checkable/Process.h"
#include "collection/Collection.h"

class CheckedProcesses : public Collection<Process>
{
	public:
		virtual bool check() override;
};

