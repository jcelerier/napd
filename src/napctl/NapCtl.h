#ifndef NAPCTL_H
#define NAPCTL_H

#include <QtDBus>
#include <map>
#include <functional>
#include <memory>

class NapCtl
{
	public:
		NapCtl(const QStringList& args);
		
		
	private:
		QDBusInterface settingsInterface;
		QDBusInterface PIDInterface;
		std::map<QString, std::function<void()>> map;
};

#endif // NAPCTL_H
