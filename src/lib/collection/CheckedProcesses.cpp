#include "CheckedProcesses.h"

#include <algorithm>
#include "NotReadyException.h"

#include <QSettings>
#include <QDir>
#include <QFileInfo>
#include "Settings.h"

bool isNumeric(QString s)
{
	return std::all_of(s.cbegin(), s.cend(), 
					   [] (const QChar& c) { return c.isDigit();});
}

bool CheckedProcesses::findByBasename(const QString& basename)
{
	const QDir dir{"/proc"};
	
	for(const QFileInfo& procfile : dir.entryInfoList(QDir::Dirs))
	{
		if(isNumeric(procfile.baseName()))
		{
			const QString filename{procfile.filePath() + "/exe"};
			if(QFile::exists(filename))
			{
				const QFile exef{filename};
				if(basename == exef.readLink().split('/', QString::SkipEmptyParts).last())
					return true;
			}
		}
	}
	
	return false;
}

bool CheckedProcesses::findByCmdline(const QString& cmdline)
{
	const QDir dir{"/proc"};
	
	for(const QFileInfo& procfile : dir.entryInfoList(QDir::Dirs))
	{
		if(isNumeric(procfile.baseName()))
		{
			const QString filename{procfile.filePath() + "/cmdline"};
			if(QFile::exists(filename))
			{
				QFile cmdf{filename};
				cmdf.open(QIODevice::ReadOnly);
				
				const QString s{cmdf.readAll().constData()};
				
				if(s == cmdline)
					return true;
			}
		}
	}
	
	return false;
}

bool CheckedProcesses::findByPath(const QString& path)
{
	const QDir dir{"/proc"};
	
	for(const QFileInfo& procfile : dir.entryInfoList(QDir::Dirs))
	{
		if(isNumeric(procfile.baseName()))
		{
			const QString filename{procfile.filePath() + "/exe"};
			if(QFile::exists(filename))
			{
				const QFile exef{filename};
				if(path == exef.readLink())
					return true;
			}
		}
	}
	
	return false;
}

bool CheckedProcesses::check() const
{
	return std::all_of(elements.cbegin(),
					   elements.cend(),
					   [] (const Process& proc) 
	{ 
		bool val{};
		if(proc.path.isSet)
			val |= findByPath(proc.path());
		
		if(proc.basename.isSet)
			val |= findByBasename(proc.basename());
		
		if(proc.cmdline.isSet)
			val |= findByCmdline(proc.cmdline());
		
		if(val) 
			throw NotReady(proc.timeout);
		
		return true;
	});
}


void CheckedProcesses::load(const Settings& s)
{
	this->elements.clear();
	QDir dir{baseFolder + "/active"};
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	
	for(QFileInfo& file : dir.entryInfoList())
	{
		const QSettings settingsFile{file.absoluteFilePath(), QSettings::IniFormat};
		uint32_t timeout{s.defaultTimeout};
		
		if(settingsFile.contains("Process/Timeout"))
			timeout = settingsFile.value("Process/Timeout").toUInt();
		
		Process p{timeout};
		
		if(settingsFile.contains("Process/MatchingPath"))
			p.path.set(settingsFile.value("Process/MatchingPath").toString());
		
		if(settingsFile.contains("Process/MatchingBasename"))
			p.basename.set(settingsFile.value("Process/MatchingBasename").toString());
					
		if(settingsFile.contains("Process/MatchingCmdline"))
			p.cmdline.set(settingsFile.value("Process/MatchingCmdline").toString());
		
		
		this->elements.push_back(p);
	}
}