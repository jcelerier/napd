#include "ProcessHandler.h"
#include <unistd.h>

ProcessHandler::ProcessHandler(std::string username):
	QProcess()
{
	userdata = getpwnam(username.c_str());
	
	if(!userdata) 
		throw std::runtime_error("Non-existent user");
}

void ProcessHandler::setupChildProcess()
{
	setuid(userdata->pw_uid);
	setgid(userdata->pw_gid);
}
