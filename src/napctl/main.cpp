#include <QCoreApplication>
#include "NapCtl.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QCoreApplication::setApplicationName("napctl");
	QCoreApplication::setApplicationVersion("0.1");
	
	QCommandLineParser parser;
	parser.setApplicationDescription("A control utility for napd");
	parser.addHelpOption();
	parser.addVersionOption();
	
	parser.addPositionalArgument("command",
								 "Command to execute. Either enable, disable, add-pid, remove-pid.");
	
	parser.addPositionalArgument("argument", "Argument to the command.");
	parser.addPositionalArgument("argument2", "Argument to the command.");
	
	parser.process(a);
	const QStringList args = parser.positionalArguments();
	
	NapCtl napctl{args};
	
	return 0;
}
