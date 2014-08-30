#pragma once
#include "checkable/CustomCheck.h"
#include "collection/Collection.h"

class CustomChecks : public CheckableCollection<CustomCheck>
{
	public:
		virtual bool check() override;
		virtual void loadSettings(Settings& s) override;
};
