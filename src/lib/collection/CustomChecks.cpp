#include "CustomChecks.h"
#include "ProcessHandler.h"
#include <algorithm>
#include "NotReadyException.h"

#include "Settings.h"
#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

bool CustomChecks::check() const
{	
	return  std::all_of(elements.cbegin(),
						elements.cend(),
						[] (const CustomCheck& customCheck)
	{
		ProcessHandler p{customCheck.user};
		
		p.start("bash", {"-c", QString("'%1'").arg(customCheck.exec)});
		p.waitForStarted();
		p.waitForFinished();
		
		const bool val{p.exitCode() == customCheck.mustEqual};
		
		if(!val)
			throw NotReady(customCheck.timeout);
		
		return val;
	});
}

void CustomChecks::load(const Settings& s)
{
	this->elements.clear();
	QDir dir{baseFolder + "/active"};
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		const QSettings settingsFile{file.absoluteFilePath(), QSettings::IniFormat};
		
		QString exec;
		uint32_t timeout{s.defaultTimeout};
		QString user{s.defaultUser};
		int mustEqual{s.defaultReturnCode};
		
		// Mandatory
		if(settingsFile.contains("Check/Exec"))
			exec = settingsFile.value("Check/Exec").toString();
		else
		{
			qWarning() << "Invalid unit file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(settingsFile.contains("Check/Timeout"))
			timeout = settingsFile.value("Check/Timeout").toUInt();
		if(settingsFile.contains("Check/MustEqual"))
			timeout = settingsFile.value("Check/MustEqual").toInt();
		if(settingsFile.contains("Check/AsUser"))
			user = settingsFile.value("Check/AsUser").toString();
		
		
		this->elements.emplace_back(std::move(exec),
									std::move(user), 
									mustEqual, 
									timeout);
	}
}