#pragma once

#include <QtDBus/QtDBus>

class PowerManager
{
	public:
		PowerManager();
		void sleep();
		void poweroff();
		
	private:
		QDBusInterface iface{"org.freedesktop.login1", 
							 "/org/freedesktop/login1", 
							 "org.freedesktop.login1.Manager", 
							 QDBusConnection::systemBus()};
		
		
};
