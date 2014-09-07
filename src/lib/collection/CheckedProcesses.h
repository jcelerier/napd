#pragma once
#include "checkable/Process.h"
#include "collection/Collection.h"
#include <QString>

class QString;
class CheckedProcesses : public CheckableCollection<Process>
{
	public:
		CheckedProcesses():
			CheckableCollection<Process>{"/etc/napd/processes.d", "process"}
		{
		}

		virtual bool check() const override;
		virtual void load(const Settings& s) override;
		
	private:
		static bool findByCmdline(const QString& cmdline);
		static bool findByPath(const QString& path);
		static bool findByBasename(const QString& basename);
};

