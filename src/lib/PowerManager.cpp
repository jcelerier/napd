#include "PowerManager.h"

PowerManager::PowerManager()
{
	if (!QDBusConnection::systemBus().isConnected()) 
	{
		throw std::runtime_error("Could not connect to dbus");
	}
	
	if (!iface.isValid()) 
	{
		throw std::runtime_error(qPrintable(QDBusConnection::sessionBus().lastError().message()));
	}
}


void PowerManager::sleep()
{
	QDBusReply<QString> reply = iface.call("CanSuspend");
	if (reply.isValid()) 
	{
		qDebug() << "org.freedesktop.login1.CanSuspend() = " << qPrintable(reply.value());
		iface.call("Suspend");
		return;
	}
	else
	{
		qDebug() << "Reply error: " << qPrintable(reply.error().message());
	}
}
