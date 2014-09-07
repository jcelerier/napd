#pragma once
#include "checkable/CustomCheck.h"
#include "collection/Collection.h"

class CustomChecks : public CheckableCollection<CustomCheck>
{
	public:
		CustomChecks():
			CheckableCollection<CustomCheck>{"/etc/napd/checks.d", "check"}
		{
		}
		
		virtual bool check() const override;
		virtual void load(const Settings& s) override;
};
