#pragma once
#include <vector>

class Settings;

class CheckableCollectionInterface
{
	public:
		virtual ~CheckableCollectionInterface() = default;
		
		// Returns true if the collection allows to go to suspend state.
		// ex. : no processes are running
		virtual bool check() = 0;
		
		// Loads settings from disk
		virtual void loadSettings(Settings& s) = 0;
};

template<typename T>
class CheckableCollection : public CheckableCollectionInterface
{
	protected:
		std::vector<T> elements;
};
