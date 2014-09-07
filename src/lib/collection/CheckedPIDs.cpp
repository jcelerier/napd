#include "CheckedPIDs.h"
#include <algorithm>
#include <QFile>
#include <QtDBus>
#include "NotReadyException.h"
#include "DBusManager.h"

using namespace std;

CheckedPIDs::CheckedPIDs(uint32_t def_timeout):
	QObject{},
	QDBusContext{},
	CheckableCollection<PID>{},
	defaultTimeout{def_timeout}
{
	DBusManager::registerObject("/PID", this);
}

bool CheckedPIDs::check() const
{
	return all_of(elements.cbegin(),
					   elements.cend(),
					   [&] (const PID& p)
	{
		if(QFile::exists(QString("/proc/%1").arg(p.pid)))
		{
			throw NotReady(p.timeout);
		}
		return true;
	});
}

void CheckedPIDs::load(const Settings& )
{
}

void CheckedPIDs::add(pid_t , quint32 pid)
{
	if(find(elements.begin(), elements.end(), pid) == elements.end())
	{
		elements.push_back(PID(pid, defaultTimeout));
		return;
	}
	
	sendErrorReply(QDBusError::Failed, "PID is already taken");
}

void CheckedPIDs::add(qint32 , quint32 pid, quint32 timeout)
{
	if(find(elements.begin(), elements.end(), pid) == elements.end())
	{
		elements.push_back(PID(pid, timeout));
		return;
	}
	
	sendErrorReply(QDBusError::Failed, "PID is already taken");
}

void CheckedPIDs::remove(qint32 , quint32 pid)
{
	auto it = std::remove(begin(elements), 
						  end(elements), 
						  pid );
	
	elements.erase(it, end(elements));
}
