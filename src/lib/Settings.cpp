#include <QSettings>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#include "Settings.h"

using namespace std;

#include "collection/CheckedProcesses.h"
#include "collection/CustomChecks.h"
#include "collection/CheckedUnits.h"
#include "collection/CheckedPIDs.h"

#include "DBusManager.h"

void Settings::enable(qint32 napctl_pid, QString s)
{
	// Find if the string corresponds to a file in either of the collections
	// If not specified, check for all .process, .unit, .checks, and file with the same name and enable 'em.
	// Example : "napctl enable vlc" will search for vlc in all folders, vlc.process in the processes.d folder, vlc.unit in the units folder, etc.
	
	// If yes, create symoblic link in the collection folder

	bool ok{true};
	for(auto& check : checks)
	{
		ok &= check->enable(napctl_pid, s);
	}
	
	if(!ok)
		sendErrorReply(QDBusError::Failed, "Error while trying to enable '" + s + "'. Please check the journal.");
}

void Settings::disable(qint32 napctl_pid, QString s)
{
	bool ok{true};
	for(auto& check : checks)
	{
		ok &= check->disable(napctl_pid, s);
	}
	
	if(!ok)
		sendErrorReply(QDBusError::Failed, "Error while trying to disable '" + s + "'. Please check the journal.");
}

Settings::Settings():
	QObject{},
	QDBusContext{}
{
	// Load base settings
	const QSettings settingsFile{"/etc/napd/napd.conf"};
	
	if(settingsFile.contains("napd/DefaultTimeout"))
		defaultTimeout = settingsFile.value("napd/DefaultTimeout").toUInt();
	
	if(settingsFile.contains("napd/DefaultUser"))
		defaultUser = settingsFile.value("napd/DefaultUser").toString();
	else
		defaultUser = QString(getpwuid(getuid())->pw_name);
	

	// Load per-check settings
	checks.emplace_back(std::unique_ptr<CheckedProcesses>(new CheckedProcesses));
	checks.emplace_back(std::unique_ptr<CheckedUnits>(new CheckedUnits));
	checks.emplace_back(std::unique_ptr<CustomChecks>(new CustomChecks));
	checks.emplace_back(std::unique_ptr<CheckedPIDs>(new CheckedPIDs(defaultTimeout)));
	
	for(auto& check : checks)
		check->load(*this);
	
	DBusManager::registerObject("/Settings", this);
}