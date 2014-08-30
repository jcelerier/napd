#include "CheckedUnits.h"
#include "NotReadyException.h"

#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <string>
#include "Settings.h"

bool CheckedUnits::check()
{
	return std::none_of(std::begin(elements),
						std::end(elements),
						[&] (Unit& unit)
	{
		QDBusReply<QString> rep = iface.call("GetUnit", unit.name.c_str());
		
		if(!rep.isValid())
			return false;
		
		std::string obj = rep.value().toStdString();
		
		QDBusInterface in{"org.freedesktop.systemd1", 
						  QString::fromStdString(obj), 
						  "org.freedesktop.systemd1.Unit", 
						  QDBusConnection::systemBus()};
		
		bool val = in.property("SubState").toString() == "Running";
		if(val)
			throw NotReady(unit.timeout);
		
		return val;
	});
}

void CheckedUnits::loadSettings(Settings& s)
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
		
		
		this->elements.emplace_back(name, timeout);
	}
}