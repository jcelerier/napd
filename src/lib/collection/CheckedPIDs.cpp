#include "CheckedPIDs.h"
#include <algorithm>
#include <QFile>
#include <QtDBus>
#include "NotReadyException.h"
#include "DBusManager.h"

CheckedPIDs::CheckedPIDs():
	QObject{},
	CheckableCollection<PID>{}
{
	DBusManager::registerObject("/PID", this);
}

bool CheckedPIDs::check() const
{
	return std::all_of(elements.cbegin(),
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

void CheckedPIDs::load(const Settings& s)
{
}
