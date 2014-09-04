#include "NapCtl.h"
#include <QtDBus>

NapCtl::NapCtl(const QStringList& args):
	settingsInterface{
		  "org.freedesktop.napd", 
		  "/Settings", 
		  "", 
		  QDBusConnection::sessionBus()},
	PIDInterface{
		  "org.freedesktop.napd", 
		  "/PID", 
		  "", 
		  QDBusConnection::sessionBus()}
{
	if(args.size() < 2 || args.size() > 3) throw std::runtime_error("Not enough arguments");
	
	if(args[0] == "add-pid")
	{
		bool PIDok;
		quint32 PID{args[1].toUInt(&PIDok)};
		if(!PIDok)
			throw std::runtime_error("Bad PID");
		
		switch(args.size())
		{
			case 2:
			{
				QDBusError rep = PIDInterface.call("add", PID);
				
				if(rep.type() != QDBusError::NoError)
					qWarning("Error (%s) : %s", rep.errorString(rep.type()).toLatin1().constData(), rep.message().toLatin1().constData());
				
				break;
			}
			case 3:
			{
				bool Timeok;
				quint32 Time{args[2].toUInt(&Timeok)};
				
				if(!Timeok)
					throw std::runtime_error("Bad timeout");
				
				QDBusError rep = PIDInterface.call("add", PID, Time);
				
				if(rep.type() != QDBusError::NoError)
					qWarning("Error (%s) : %s", rep.errorString(rep.type()).toLatin1().constData(), rep.message().toLatin1().constData());
				
				break;
			}
		}
	}
	else if(args[0] == "remove-pid")
	{
		bool PIDok;
		PIDInterface.call("remove", quint32(args[1].toUInt(&PIDok)));

		if(!PIDok)
			throw std::runtime_error("Bad PID");
	}
	else if(args[0] == "enable")
	{
		settingsInterface.call("enable", args[1]);
	}
	else if(args[0] == "disable")
	{
		settingsInterface.call("disable", args[1]);
	}
	else
	{
		throw std::runtime_error("Unknown action");
	}
}
