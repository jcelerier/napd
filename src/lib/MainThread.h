#pragma once
#include <QTimer>

#include "PowerManager.h"
#include "Setup.h"

class MainThread: public QObject
{
		Q_OBJECT
	public:
		MainThread(QObject* parent);

	public slots:
		void performChecks();
		
	private:
		Settings settings;
		PowerManager power;
		QTimer* timer{new QTimer(nullptr)};
};

