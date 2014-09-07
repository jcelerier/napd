#pragma once

#include <QtDBus>
#include <QMap>
#include <functional>
#include <memory>
#include <unistd.h>

#include "MessageListener.h"
class NapCtl
{
	public:
		NapCtl(const QStringList& args);
		
		void addPID();
		void removePID();
		
		void enable();
		void disable();
		
		
	private:
		const QStringList& args;
		QDBusInterface settingsInterface;
		QDBusInterface PIDInterface;
		MessageListener listener;
		
		QMap<QString, std::function<void()>> actionsMap
			{
				{"add-pid", std::bind(&NapCtl::addPID, this)},
				{"remove-pid", std::bind(&NapCtl::removePID, this)},
				{"enable", std::bind(&NapCtl::enable, this)},
				{"disable", std::bind(&NapCtl::disable, this)}
			};
		
		pid_t localPID{getpid()};
};
