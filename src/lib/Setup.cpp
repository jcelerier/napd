#include "Setup.h"
#include <QDir>
#include <QDebug>
#include <QSettings>
#include <cinttypes>

using namespace std;

Setup::Setup(Settings& s)
{
	readProcesses(s);
	readUnits(s);
	readChecks(s);
}

//TODO champ type à la place
void Setup::readProcesses(Settings& s)
{
	QDir dir("/etc/napd/processes.d");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		QSettings set(file.absoluteFilePath(), QSettings::IniFormat);
		auto name = set.value("Process/ProcessName").toString().toStdString();
		uint32_t timeout = 0;
		
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
		auto name = set.value("Unit/UnitName").toString().toStdString();
		uint32_t timeout = 0;
		
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
		auto exec = set.value("Check/Exec").toString().toStdString();
		uint32_t timeout = 0;
		std::string user = "root";
		int mustEqual = 0;
		
		if(set.contains("Check/Timeout"))
			timeout = set.value("Check/Timeout").toUInt();
		if(set.contains("Check/MustEqual"))
			timeout = set.value("Check/MustEqual").toInt();
		if(set.contains("Check/AsUser"))
			user = set.value("Check/AsUser").toString().toStdString();
		
		s.customChecks.add(CustomCheck(exec, user, mustEqual, timeout));
	}
}
