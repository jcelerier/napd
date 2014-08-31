#pragma once
#include <vector>

class Settings;

class CheckableCollectionInterface
{
	public:
		virtual ~CheckableCollectionInterface() = default;
		
		// Returns true if the collection allows to go to suspend state.
		// ex. : no processes are running
		virtual bool check() const = 0;
		
		// Loads settings from disk
		virtual void loadSettings(const Settings& s) = 0;
};

template<typename T>
class CheckableCollection : public CheckableCollectionInterface
{
	protected:
		std::vector<T> elements;
};
