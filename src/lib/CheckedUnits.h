#pragma once
#include "checkable/Unit.h"
#include "collection/Collection.h"

#include <QtDBus>

class CheckedUnits : public Collection<Unit>
{
	public:
		virtual bool check() override;
		
	private:
		QDBusInterface iface{"org.freedesktop.systemd1", 
							 "/org/freedesktop/systemd1", 
							 "org.freedesktop.systemd1.Manager", 
							 QDBusConnection::systemBus()};
};

