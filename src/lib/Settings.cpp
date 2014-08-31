#include <QSettings>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

#include "Settings.h"
#include "CheckedProcesses.h"
#include "CheckedUnits.h"
#include "CustomChecks.h"

using namespace std;

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
	checks.emplace_back(std::make_unique<CheckedProcesses>());
	checks.emplace_back(std::make_unique<CheckedUnits>());
	checks.emplace_back(std::make_unique<CustomChecks>());
	
	for(auto& check : checks)
		check->loadSettings(*this);
}