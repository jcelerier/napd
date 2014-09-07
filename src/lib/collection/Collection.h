#pragma once
#include <vector>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QFile>

#include <QDebug>
#include <QtDBus>
class Settings;

class CheckableCollectionInterface
{
	public:
		virtual ~CheckableCollectionInterface() = default;
		
		// Returns true if the collection allows to go to suspend state.
		// ex. : no processes are running
		virtual bool check() const = 0;
		
		// Loads settings from disk
		virtual void load(const Settings&) = 0;
		
		virtual bool enable(pid_t napctl_pid, const QString&) const = 0;
		virtual bool disable(pid_t napctl_pid, const QString&) const = 0;
};


template<typename T>
class CheckableCollection : public CheckableCollectionInterface
{
	public:
		CheckableCollection() = default;
		CheckableCollection(QString&& folder, QString&& ext):
			baseFolder{std::move(folder)},
			extension{std::move(ext)}
		{
		}

		virtual bool enable(pid_t napctl_pid, const QString & s) const override
		{
			QDBusMessage call = QDBusMessage::createMethodCall("org.freedesktop.napctl-" + QString::number(napctl_pid), 
															   "/Message", 
															   "", 
															   "message");
			
			bool ok{true};
			if(baseFolder.isEmpty()) return true;
			
			const QDir dir{baseFolder};
			if(!dir.exists()) return true;
			
			for(const QFileInfo& file_info : dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks))
			{
				if(file_info.fileName() == s ||
						file_info.fileName() == (s + "." + extension))
				{
					QString activeName{baseFolder + "/active/" + file_info.fileName()};
					if(QFile::exists(activeName))
					{
						QString args = "Already running : " + activeName + ".";
						call.setArguments({args});
						QDBusConnection::sessionBus().asyncCall(call);
						
						qDebug("%s", args.toLatin1().constData());
						continue;
					}
					
					QFile f{file_info.absoluteFilePath()};
					bool tmpok = f.link(activeName);
					
					if(!tmpok)
					{
						qWarning() << "Could not create the link from" 
								   << file_info.absoluteFilePath() << "to" << activeName;
					}
					else
					{
						QString args = "Activated : " + activeName + ".";
						call.setArguments({args});
						QDBusConnection::sessionBus().asyncCall(call);
						
						qDebug("%s", args.toLatin1().constData());
					}
					ok &= tmpok;
				}
			}
			
			return ok;
		}
		
		
		virtual bool disable(pid_t napctl_pid, const QString & s) const override
		{
			QDBusMessage call = QDBusMessage::createMethodCall("org.freedesktop.napctl-" + QString::number(napctl_pid), 
															   "/Message", 
															   "", 
															   "message");
			
			bool ok{true};
			const QDir dir{baseFolder + "/active"};
			if(!dir.exists()) return true;
			
			for(const QFileInfo& file_info : dir.entryInfoList(QDir::Files | QDir::Hidden))
			{
				if(file_info.fileName() == s ||
						file_info.fileName() == (s + "." + extension))
				{
					QFile f{file_info.absoluteFilePath()};
					bool tmpok = f.remove();
					
					if(!tmpok)
					{
						qWarning() << "Could not remove the link :" << file_info.absoluteFilePath();
					}
					else
					{
						QString args = "Deactivated : " + file_info.absoluteFilePath() + ".";
						call.setArguments({args});
						QDBusConnection::sessionBus().asyncCall(call);
						
						qDebug("%s", args.toLatin1().constData());
					}
					
					ok &= tmpok;
				}
			}
			
			return ok;
		}
		
		
	protected:
		std::vector<T> elements;
		const QString baseFolder;
		const QString extension;
};
