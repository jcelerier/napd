#include "CheckedUnits.h"
#include "NotReadyException.h"

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
