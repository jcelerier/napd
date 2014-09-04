#pragma once
#include <QString>
#include <QObject>

class DBusManager
{
	public:
		DBusManager();
		
		static void registerObject(const QString& path, QObject* obj);
};
