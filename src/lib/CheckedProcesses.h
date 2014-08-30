#pragma once
#include "checkable/Process.h"
#include "collection/Collection.h"
#include <QString>

class QString;
class CheckedProcesses : public CheckableCollection<Process>
{
	public:
		virtual bool check() override;
		virtual void loadSettings(Settings& s) override;
		
	private:
		void find_process(QString name);
};

