#pragma once
#include "Collection.h"
#include "checkable/PID.h"
#include <QDebug>

class CheckedPIDs : public QObject, public CheckableCollection<PID>
{
		Q_OBJECT
	public:
		CheckedPIDs();
		
		virtual bool check() const override;
		virtual void load(const Settings& ) override;
		
	public slots:
		Q_SCRIPTABLE void add(quint32 pid)
		{
			qDebug() << "Addin " << pid;
			elements.push_back(PID(pid, 240));
		}
		
		Q_SCRIPTABLE void add(quint32 pid, quint32 timeout)
		{
			qDebug() << "Addin " << pid << " with timeout " << timeout;
			elements.push_back(PID(pid, timeout));
		}
		
		Q_SCRIPTABLE void remove(quint32 pid)
		{
			qDebug() << "Removin " << pid;
			 elements.erase( std::remove( std::begin(elements), std::end(elements), pid ), std::end(elements) ); 
		}
		
		
};