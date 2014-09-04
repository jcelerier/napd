#include "DBusManager.h"
#include <QtDBus>

DBusManager::DBusManager()
{
	if(!QDBusConnection::sessionBus().isConnected())
	{
		qWarning() << "Cannot connect to D-Bus session bus";
	}
	
	QDBusConnection::sessionBus().unregisterService("org.freedesktop.napd");
	if(!QDBusConnection::sessionBus().registerService("org.freedesktop.napd"))
	{
		qWarning() << "Cannot register the napd service";
	}
}

void DBusManager::registerObject(const QString& path, QObject* obj)
{
	QDBusConnection::sessionBus().unregisterObject(path);
	QDBusConnection::sessionBus().registerObject(path, obj, QDBusConnection::ExportScriptableSlots);
}
