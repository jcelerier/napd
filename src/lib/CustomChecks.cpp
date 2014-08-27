#include "CustomChecks.h"
#include "ProcessHandler.h"
#include <algorithm>
#include "NotReadyException.h"

bool CustomChecks::check()
{	
	return  std::all_of(std::begin(elements),
						 std::end(elements),
						 [] (CustomCheck& check)
	{
		ProcessHandler p(check.user);
		p.setProgram("bash");
		p.setArguments({"-c", QString("'%1'").arg(QString::fromStdString(check.exec))});
		
		p.start();
		p.waitForStarted();
		p.waitForFinished();
		
		bool val = p.exitCode() == check.mustEqual;
		
		if(!val)
			throw NotReady(check.timeout);
		
		return p.exitCode() == check.mustEqual;
	});
}