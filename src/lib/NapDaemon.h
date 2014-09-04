#pragma once
#include <QTimer>

#include "PowerManager.h"
#include "Settings.h"
#include "DBusManager.h"

class NapDaemon: public QObject
{
		Q_OBJECT
	public:
		NapDaemon(QObject*);

	public slots:
		void performChecks();
		
	private:
		DBusManager dbus;
		Settings settings;
		PowerManager power;
		QTimer timer{nullptr};
};

