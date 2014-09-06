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

void Settings::enable(QString s)
{
	qWarning() << "TODO";
}

void Settings::disable(QString s)
{
	qWarning() << "TODO";
}

Settings::Settings()
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