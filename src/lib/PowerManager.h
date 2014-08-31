#pragma once

#include <QtDBus/QtDBus>

class PowerManager
{
	public:
		PowerManager();
		void suspend() const;
		void poweroff() const;
		
	private:
		QDBusInterface* iface;
};
