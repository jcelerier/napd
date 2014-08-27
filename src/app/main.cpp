#include <QCoreApplication>

#include "NapDaemon.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	
	NapDaemon t{&app};
	
	return app.exec();
}

