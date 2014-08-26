#pragma once
#include "checkable/CustomCheck.h"
#include "collection/Collection.h"

class CustomChecks : public Collection<CustomCheck>
{
	public:
		virtual bool check() override;
};
