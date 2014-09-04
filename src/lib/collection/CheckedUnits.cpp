#include "CheckedUnits.h"
#include "NotReadyException.h"

#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include "Settings.h"

bool CheckedUnits::check() const
{
	return std::all_of(elements.cbegin(),
					   elements.cend(),
					   [&] (const Unit& unit)
	{
		const QDBusReply<QString> rep{iface->call("GetUnit", 
												  unit.name.toLatin1().constData())};
		
		if(!rep.isValid())
			return false;
		
		const QDBusInterface in{"org.freedesktop.systemd1", 
								rep.value(), 
								"org.freedesktop.systemd1.Unit", 
								QDBusConnection::systemBus()};
		
		const bool val{in.property("SubState").toString() == "Running"};
		
		if(val)
			throw NotReady(unit.timeout);
		
		return true;
	});
}

void CheckedUnits::load(const Settings& s)
{
	QDir dir{"/etc/napd/units.d/active"};
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		const QSettings set{file.absoluteFilePath(), QSettings::IniFormat};
		uint32_t timeout{s.defaultTimeout};
		QString name;
		
		// Mandatory
		if(set.contains("Unit/UnitName"))
			name = set.value("Unit/UnitName").toString();
		else
		{
			qWarning() << "Invalid unit file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(set.contains("Unit/Timeout"))
			timeout = set.value("Unit/Timeout").toUInt();
		
		
		this->elements.emplace_back(std::move(name), 
									timeout);
	}
}