#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

#include <QObject>
#include <QDebug>
#include <unistd.h>
#include <QThread>

class MessageListener : public QObject
{
		Q_OBJECT
	public:
		explicit MessageListener(QObject *parent = 0);
		~MessageListener();
		
	signals:
		
	public slots:
		Q_SCRIPTABLE void message(QString m)
		{
			qDebug() << m;
		}
		
	private:
		QString serviceName{"org.freedesktop.napctl-" + QString::number(getpid())};
		QThread t;
};

#endif // MESSAGELISTENER_H
