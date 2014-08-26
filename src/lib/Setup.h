#ifndef SETUP_H
#define SETUP_H

#include "Settings.h"
class Setup
{
	public:
		Setup(Settings& s);
		
	private:
		void readGlobalSettings();
		void readProcesses(Settings& s);
		void readUnits(Settings& s);
		void readChecks(Settings& s);
		
};

#endif // SETUP_H
