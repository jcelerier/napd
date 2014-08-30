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
	QSettings set("/etc/napd/napd.conf");
	
	if(set.contains("napd/DefaultTimeout"))
		defaultTimeout = set.value("napd/DefaultTimeout").toUInt();
	
	if(set.contains("napd/DefaultUser"))
		defaultUser = set.value("napd/DefaultUser").toString().toStdString();
	else
		defaultUser = std::string(getpwuid(getuid())->pw_name);
	

	// Load per-check settings
	checks.emplace_back(std::make_unique<CheckedProcesses>());
	checks.emplace_back(std::make_unique<CheckedUnits>());
	checks.emplace_back(std::make_unique<CustomChecks>());
	
	for(auto& check : checks)
		check->loadSettings(*this);
}