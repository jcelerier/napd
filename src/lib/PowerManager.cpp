#include "PowerManager.h"

PowerManager::PowerManager():
	iface(new QDBusInterface{
		  "org.freedesktop.login1", 
		  "/org/freedesktop/login1", 
		  "org.freedesktop.login1.Manager", 
		  QDBusConnection::systemBus()})
{
	if (!QDBusConnection::systemBus().isConnected()) 
	{
		throw std::runtime_error("Could not connect to dbus");
	}
	
	if (!iface->isValid()) 
	{
		throw std::runtime_error(qPrintable(QDBusConnection::systemBus().lastError().message()));
	}
}

void PowerManager::suspend() const
{
	const QDBusReply<QString> reply{iface->call("CanSuspend")};
	
	if (reply.isValid()) 
	{
		if(reply.value() != "yes") 
		{
			qWarning() << "Cannot suspend.";
			return;
		}
		
		const QDBusReply<void> rep{iface->call("Suspend", false)};
		
		if(!reply.isValid())
			qWarning() << "Reply error: " << qPrintable(rep.error().message());
	}
	else
	{
		qWarning() << "Reply error: " << qPrintable(reply.error().message());
	}
}
