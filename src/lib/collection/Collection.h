#pragma once
#include <vector>

template<typename T>
class Collection
{
	public:
		virtual ~Collection() = default;
		void add(T&& element)
		{
			elements.emplace_back(element);
		}

		// Returns true if the collection allows to go to suspend state.
		// ex. : no processes are running
		virtual bool check() = 0;
		
	protected:
		std::vector<T> elements;
};
