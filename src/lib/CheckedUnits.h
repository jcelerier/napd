#pragma once
#include "checkable/Unit.h"
#include "collection/Collection.h"

#include <QtDBus>

class CheckedUnits : public CheckableCollection<Unit>
{
	public:
		virtual bool check() override;
		virtual void loadSettings(Settings& s) override;
		
	private:
		QDBusInterface iface{"org.freedesktop.systemd1", 
							 "/org/freedesktop/systemd1", 
							 "org.freedesktop.systemd1.Manager", 
							 QDBusConnection::systemBus()};
};

