#include "CustomChecks.h"
#include <QProcess>
#include <algorithm>

bool CustomChecks::check()
{	
	return  std::all_of(std::begin(elements),
						 std::end(elements),
						 [] (CustomCheck& check)
	{
		QProcess p;
		p.setProgram("bash");
		p.setArguments({"-c", QString("'%1'").arg(QString::fromStdString(check.exec))});

		p.start();
		p.waitForStarted();
		p.waitForFinished();
		
		return p.exitCode() == check.mustEqual;
	});
}