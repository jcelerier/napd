#pragma once
#include "checkable/CustomCheck.h"
#include "collection/Collection.h"

class CustomChecks : public CheckableCollection<CustomCheck>
{
	public:
		virtual bool check() const override;
		virtual void load(const Settings& s) override;
};
