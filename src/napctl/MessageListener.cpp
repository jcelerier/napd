#include "MessageListener.h"
#include <QtDBus>
#include <unistd.h>

MessageListener::MessageListener(QObject *parent) :
	QObject(parent)
{
	if(!QDBusConnection::sessionBus().isConnected())
	{
		qWarning() << "Cannot connect to D-Bus session bus";
	}
	
	QDBusConnection::sessionBus().unregisterService(serviceName);
	if(!QDBusConnection::sessionBus().registerService(serviceName))
	{
		qWarning() << "Cannot register the service: " << serviceName;
	}
	
	QDBusConnection::sessionBus().registerObject("/Messages", this, QDBusConnection::ExportScriptableSlots);
	
	t.start();
	this->moveToThread(&t);
}

MessageListener::~MessageListener()
{
	QDBusConnection::sessionBus().unregisterService(serviceName);
	t.quit();
	t.wait();
}
