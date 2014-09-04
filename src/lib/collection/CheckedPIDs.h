#pragma once
#include "Collection.h"
#include "checkable/PID.h"
#include <QDebug>
#include <QtDBus>
#include <cinttypes>

class CheckedPIDs : public QObject, public QDBusContext, public CheckableCollection<PID>
{
		Q_OBJECT
	public:
		CheckedPIDs(uint32_t def_timeout);
		
		virtual bool check() const override;
		virtual void load(const Settings& ) override;
		
	public slots:
		Q_SCRIPTABLE void add(quint32 pid);
		Q_SCRIPTABLE void add(quint32 pid, quint32 timeout);
		
		Q_SCRIPTABLE void remove(quint32 pid);
		
	private:
		uint32_t defaultTimeout;
};