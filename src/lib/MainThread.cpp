#include "MainThread.h"
#include "NotReadyException.h"

MainThread::MainThread(QObject* parent):
	QObject(parent)
{
	Setup{settings};
	
	connect(timer, &QTimer::timeout, 
			this, &MainThread::performChecks);
	
	timer->start(settings.defaultTimeout * 1000);
}

void MainThread::performChecks()
{
	try
	{
		bool ready2go = settings.checkedProcesses.check() && 
						settings.checkedUnits.check() &&
						settings.customChecks.check();

		if(ready2go)
		 {
			 timer->start(settings.defaultTimeout * 1000);
			 power.suspend();
		 }
	}
	catch(NotReady& e)
	{
		timer->start(e.timeout * 1000);
	}
}
