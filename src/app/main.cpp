#include <iostream>
#include <QtCore>

#include "Setup.h"
#include "MainThread.h"

using namespace std;

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	
	MainThread t(&app);
	Setup{t.settings};
	
	t.start();
	
	
	return app.exec();
}

