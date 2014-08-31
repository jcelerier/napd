#include "ProcessHandler.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

ProcessHandler::ProcessHandler(const QString& username):
	QProcess()
{
	userdata = getpwnam(username.toLatin1().constData());
	
	if(!userdata) 
		throw std::runtime_error("Non-existent user");
}

void ProcessHandler::setupChildProcess()
{
	setuid(userdata->pw_uid);
	setgid(userdata->pw_gid);
}
