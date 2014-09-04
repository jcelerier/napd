#include "NapDaemon.h"
#include "NotReadyException.h"

#include "collection/CheckedProcesses.h"
#include "collection/CustomChecks.h"
#include "collection/CheckedUnits.h"
#include "collection/CheckedPIDs.h"

NapDaemon::NapDaemon(QObject* pobj):
	QObject{pobj}
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
		for(const auto& check : settings.checks)
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
