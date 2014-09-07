#pragma once
#include <cinttypes>
#include <memory>
#include "collection/Collection.h"

#include <QObject>
#include <QDBusContext>
class Settings : public QObject, public QDBusContext
{
		Q_OBJECT

	public slots:
		Q_SCRIPTABLE void enable(qint32 napctl_pid, QString s);
		Q_SCRIPTABLE void disable(qint32 napctl_pid, QString);
		
	public:
		Settings();
		
		std::vector<std::unique_ptr<CheckableCollectionInterface>> checks;
		
		// Default data
		uint32_t defaultTimeout{60};

		// Custom checks
		QString defaultUser{};
		int defaultReturnCode{};
};
