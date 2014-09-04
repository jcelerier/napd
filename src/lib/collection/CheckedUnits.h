#pragma once
#include "checkable/Unit.h"
#include "collection/Collection.h"

#include <QtDBus>

class CheckedUnits : public CheckableCollection<Unit>
{
	public:
		CheckedUnits():
			iface{new QDBusInterface{
				  "org.freedesktop.systemd1", 
				  "/org/freedesktop/systemd1", 
				  "org.freedesktop.systemd1.Manager", 
				  QDBusConnection::systemBus()}}
		{
			if (!iface->isValid()) 
			{
				throw std::runtime_error(qPrintable(QDBusConnection::systemBus().lastError().message()));
			}
		}

		virtual bool check() const override;
		virtual void load(const Settings& s) override;
		
	private:
		QDBusInterface* iface;
};

