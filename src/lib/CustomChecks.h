#pragma once
#include "checkable/CustomCheck.h"
#include "collection/Collection.h"

class CustomChecks : public CheckableCollection<CustomCheck>
{
	public:
		virtual bool check() const override;
		virtual void loadSettings(const Settings& s) override;
};
