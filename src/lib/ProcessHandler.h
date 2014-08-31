#pragma once
#include <QProcess>

struct passwd;
class ProcessHandler : public QProcess
{
		Q_OBJECT
	public:
		ProcessHandler(const QString& username);

	protected:
		void setupChildProcess();
		
	private:
		struct passwd * userdata{nullptr};
};