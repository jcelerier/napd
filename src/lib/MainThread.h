#pragma once
#include <QThread>
#include <QTimer>

#include "PowerManager.h"
#include "Settings.h"

class MainThread: public QThread
{
		Q_OBJECT
	public:
		MainThread(QObject* parent):
			QThread(parent)
		{
			
		}

		Settings settings;
		PowerManager power;
		
	public slots:
		void performChecks();
		
	protected:
		virtual void run();
};

