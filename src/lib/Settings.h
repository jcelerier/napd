#pragma once
#include <cinttypes>
#include <memory>
#include "collection/Collection.h"

#include <QObject>

class Settings : public QObject
{
		Q_OBJECT

	public slots:
		void enable(QString s);
		void disable(QString s);
		
	public:
		Settings();
		
		std::vector<std::unique_ptr<CheckableCollectionInterface>> checks;
		
		// Default data
		uint32_t defaultTimeout{60};

		// Custom checks
		QString defaultUser{};
		int defaultReturnCode{};
};
