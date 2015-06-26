#include "stdafx.h"
#include <vector>

namespace DiffProcessor
{
	//void fromAray(T* a)
	//{
	//	clear();
	//	for (long i = 0; i < sizeof(a) / sizeof(T); ++i)
	//	{
	//		addLast(a[i]);
	//	}
	//}
	void SortedDictionary<T>::fromVector(std::vector<T> vector)
	{
		clear();
		for (long i = 0; i < vector.size(); ++i)
		{
			addLast(a[i]);
		}
	}

	void addAfter(SortedDictionary<T>::Entry* entry, T value)
	{

	}

	void addBefore(Entry* entry, T value)
	{

	}

	void addLast(T value)
	{

	}

	void addFirst(T value)
	{

	}

	void remove(Entry* entry)
	{
		if (entry->previous != null)
			entry->previous.next = entry->Next;
		else
			first = entry->next;

		if (entry->next != null)
			entry->next->previous = entry->previous;
		else
			last = entry->previous;

		++_performedOperations;
		--_count;
		free(entry);
	}

	void clear()
	{
		Entry* entry = _first, next;
		while (entry != nullptr)
		{
			next = entry->Next;
			remove(entry);
			entry = next;
		}
		_performedOperations = 0;
		_count = 0;
	}
};