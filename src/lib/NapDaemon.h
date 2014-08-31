#pragma once
#include <QTimer>

#include "PowerManager.h"
#include "Settings.h"

class NapDaemon: public QObject
{
		Q_OBJECT
	public:
		NapDaemon(QObject*);

	public slots:
		void performChecks();
		
	private:
		Settings settings;
		PowerManager power;
		QTimer timer{nullptr};
};

