#include "NapDaemon.h"
#include "NotReadyException.h"

NapDaemon::NapDaemon(QObject* parent):
	QObject(parent)
{
	connect(&timer, &QTimer::timeout, 
			this, &NapDaemon::performChecks);
	
	timer.start(settings.defaultTimeout * 1000);
}

void NapDaemon::performChecks()
{
	try
	{
		bool ready2go{true};
		for(auto& check : settings.checks)
			ready2go &= check->check();

		if(ready2go)
		 {
			 timer.start(settings.defaultTimeout * 1000);
			 power.suspend();
		 }
	}
	catch(NotReady& e)
	{
		timer.start(e.timeout * 1000);
	}
}
