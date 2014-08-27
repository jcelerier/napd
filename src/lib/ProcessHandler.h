#pragma once
#include <QProcess>

#include <pwd.h>
#include <sys/types.h>

class ProcessHandler : public QProcess
{
		Q_OBJECT
	public:
		ProcessHandler(std::string username);

	protected:
		void setupChildProcess();
		
	private:
		struct passwd * userdata{nullptr};
};