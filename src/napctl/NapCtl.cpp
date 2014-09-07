#include "NapCtl.h"
#include <QtDBus>

NapCtl::NapCtl(const QStringList& arguments):
	args{arguments},
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
	if(!PIDInterface.isValid() || !settingsInterface.isValid())
	{
		qWarning() << "Cannot connect to the napd instance.";
		return;
	}
	
	if(actionsMap.contains(args[0]))
	{
		actionsMap[args[0]]();
	}
	else
	{
		qWarning() << "Unknown operation :" << args[0];
	}
}

void NapCtl::addPID()
{
	if(args.size() != 2 && args.size() != 3)
	{
		qWarning() << "add-pid requires a PID and an optional timeout value.";
		return ;
	}
	
	bool PIDok;
	quint32 PID{args[1].toUInt(&PIDok)};
	if(!PIDok)
	{
		qWarning() << "Bad PID.";
		return;
	}
	
	switch(args.size())
	{
		case 2:
		{
			const QDBusError rep = PIDInterface.call("add", localPID, PID);
			
			if(rep.type() != QDBusError::NoError)
				qWarning("Error (%s) : %s", 
						 QDBusError::errorString(rep.type()).toLatin1().constData(),
						 rep.message().toLatin1().constData());
			
			break;
		}
		case 3:
		{
			bool Timeok;
			quint32 Time{args[2].toUInt(&Timeok)};
			
			if(!Timeok)
			{
				qWarning() << "Bad timeout.";
				return;
			}

			const QDBusError rep = PIDInterface.call("add", localPID, PID, Time);
			
			if(rep.type() != QDBusError::NoError)
				qWarning("Error (%s) : %s", 
						 QDBusError::errorString(rep.type()).toLatin1().constData(), 
						 rep.message().toLatin1().constData());
			
			break;
		}
	}
}

void NapCtl::removePID()
{
	if(args.size() != 2)
	{
		qWarning() << "remove-pid requires a PID.";
		return ;
	}
	
	bool PIDok;
	quint32 PID{args[1].toUInt(&PIDok)};
	if(!PIDok)
	{
		qWarning() << "Bad PID.";
		return;
	}
	
	PIDInterface.call("remove", localPID, PID);
}

void NapCtl::enable()
{
	if(args.size() != 2)
	{
		qWarning() << "enable requires a file name. See /{etc,lib}/napd/{checks,processes,units}.d.";
		return ;
	}
	
	const QDBusError rep = settingsInterface.call("enable", localPID, args[1]);
	if(rep.type() != QDBusError::NoError)
		qWarning("Error (%s) : %s", 
				 QDBusError::errorString(rep.type()).toLatin1().constData(), 
				 rep.message().toLatin1().constData());
	
}

void NapCtl::disable()
{
	if(args.size() != 2)
	{
		qWarning() << "disable requires a file name. See /{etc,lib}/napd/{checks,processes,units}.d.";
		return ;
	}
	
	const QDBusError rep = settingsInterface.call("disable", localPID, args[1]);
	
	if(rep.type() != QDBusError::NoError)
		qWarning("Error (%s) : %s", 
				 QDBusError::errorString(rep.type()).toLatin1().constData(), 
				 rep.message().toLatin1().constData());
	
}
