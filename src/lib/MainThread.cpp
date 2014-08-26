#include "MainThread.h"

void MainThread::performChecks()
{
	if(settings.checkedProcesses.check() && 
	   settings.checkedUnits.check() &&
	   settings.customChecks.check())
	{
		power.sleep();
	}
}

void MainThread::run()
{
	QTimer t(this);
	connect(&t, SIGNAL(timeout()), this, SLOT(performChecks()));
	
	t.start(60000);
	
	exec();	
}
