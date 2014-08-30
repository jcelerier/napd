#include "CustomChecks.h"
#include "ProcessHandler.h"
#include <algorithm>
#include "NotReadyException.h"

#include "Settings.h"
#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <string>

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

void CustomChecks::loadSettings(Settings& s)
{
	QDir dir("/etc/napd/checks.d");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		QSettings set(file.absoluteFilePath(), QSettings::IniFormat);
		
		std::string exec;
		uint32_t timeout = s.defaultTimeout;
		std::string user = s.defaultUser;
		int mustEqual = s.defaultReturnCode;
		
		// Mandatory
		if(set.contains("Check/Exec"))
			exec = set.value("Check/Exec").toString().toStdString();
		else
		{
			qWarning() << "Invalid unit file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(set.contains("Check/Timeout"))
			timeout = set.value("Check/Timeout").toUInt();
		if(set.contains("Check/MustEqual"))
			timeout = set.value("Check/MustEqual").toInt();
		if(set.contains("Check/AsUser"))
			user = set.value("Check/AsUser").toString().toStdString();
		
		
		this->elements.emplace_back(exec, user, mustEqual, timeout);
	}
}