#include "CheckedProcesses.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#include <algorithm>
#include "NotReadyException.h"

#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include <string>
#include "Settings.h"

bool isNumeric(QString s)
{
	return std::all_of(s.begin(), s.end(), 
					   [] (QChar& c) { return c.isDigit();});
}

void CheckedProcesses::find_process(QString name)
{
	QDir dir("/proc");
	for(QFileInfo& procfile : dir.entryInfoList())
	{
		if(procfile.isDir() && isNumeric(procfile.baseName()))
		{
			QFile f(procfile.filePath() + "/exe");
			if(f.exists())
			{
				QString exe = f.readLink();
				qDebug() << "Executable" << exe.split('/', QString::SkipEmptyParts).last();
				//f.open(QIODevice::ReadOnly);
				//QString s(f.readAll().constData());
				//qDebug() << "Path: " << f.fileName() << "\nString " << s;
				
			}
		}
	}
}

//TODO redo this with qt
pid_t proc_find(const char* name) 
{
	DIR* dir;
	struct dirent* ent;
	char* endptr;
	char buf[512];
	
	if (!(dir = opendir("/proc"))) {
		perror("can't open /proc");
		return -1;
	}
	
	while((ent = readdir(dir)) != NULL) {
		/* if endptr is not a null character, the directory is not
		 * entirely numeric, so ignore it */
		long lpid = strtol(ent->d_name, &endptr, 10);
		if (*endptr != '\0') {
			continue;
		}
		
		/* try to open the cmdline file */
		snprintf(buf, sizeof(buf), "/proc/%ld/cmdline", lpid);
		FILE* fp = fopen(buf, "r");
		
		if (fp) {
			if (fgets(buf, sizeof(buf), fp) != NULL) {
				/* check the first token in the file, the program name */
				char* first = strtok(buf, " ");
				if (!strcmp(first, name)) {
					fclose(fp);
					closedir(dir);
					return (pid_t)lpid;
				}
			}
			fclose(fp);
		}
		
	}
	
	closedir(dir);
	return -1;
}

bool CheckedProcesses::check()
{
	return std::all_of(std::begin(elements),
						std::end(elements),
						[] (Process& proc) 
	{ 
		bool val = proc_find(proc.name.c_str()) == -1;
		
		if(!val) throw NotReady(proc.timeout);
		return val; 
	});
}


void CheckedProcesses::loadSettings(Settings& s)
{
	QDir dir("/etc/napd/processes.d");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		QSettings set(file.absoluteFilePath(), QSettings::IniFormat);
		std::string name; 
		uint32_t timeout = s.defaultTimeout;
		
		// Mandatory
		if(set.contains("Process/ProcessName"))
			name = set.value("Process/ProcessName").toString().toStdString();
		else
		{
			qWarning() << "Invalid process file : " << file.absoluteFilePath();
			continue;
		}
		
		// Facultative
		if(set.contains("Process/Timeout"))
			timeout = set.value("Process/Timeout").toUInt();
		
		this->elements.emplace_back(name, timeout);
	}
}