#include <QCoreApplication>

#include "MainThread.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	
	MainThread t{&app};
	
	return app.exec();
}

