#include "Setup.h"
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <cinttypes>

#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

using namespace std;

Setup::Setup(Settings& s)
{
	readGlobalSettings(s);
	readProcesses(s);
	readUnits(s);
	readChecks(s);
}

void Setup::readGlobalSettings(Settings& s)
{
	QSettings set("/etc/napd/napd.conf");
	
	if(set.contains("napd/DefaultTimeout"))
		s.defaultTimeout = set.value("napd/DefaultTimeout").toUInt();
	
	if(set.contains("napd/DefaultUser"))
		s.defaultUser = set.value("napd/DefaultUser").toString().toStdString();
	else
		s.defaultUser = std::string(getpwuid(getuid())->pw_name);

}

void Setup::readProcesses(Settings& s)
{
	QDir dir("/etc/napd/processes.d");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		QSettings set(file.absoluteFilePath(), QSettings::IniFormat);
		std::string name; 
		uint32_t timeout = s.defaultTimeout;
		
		// Mandatory
		if(set.contains("Process/ProcessName"))
			name = set.value("Process/ProcessName").toString().toStdString();
		else
		{
			qWarning() << "Invalid process file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(set.contains("Process/Timeout"))
			timeout = set.value("Process/Timeout").toUInt();
		
		
		s.checkedProcesses.add(Process(name, timeout));
	}
}

void Setup::readUnits(Settings& s)
{
	QDir dir("/etc/napd/units.d");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		QSettings set(file.absoluteFilePath(), QSettings::IniFormat);
		uint32_t timeout = s.defaultTimeout;
		std::string name;
		
		// Mandatory
		if(set.contains("Unit/UnitName"))
			name = set.value("Unit/UnitName").toString().toStdString();
		else
		{
			qWarning() << "Invalid unit file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(set.contains("Unit/Timeout"))
			timeout = set.value("Unit/Timeout").toUInt();
		
		
		s.checkedUnits.add(Unit(name, timeout));
	}
}

void Setup::readChecks(Settings& s)
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
		
		
		s.customChecks.add(CustomCheck(exec, user, mustEqual, timeout));
	}
}
