#pragma once

#include "SortedLimitedList.h"

namespace DiffProcessor
{
	class Processor
	{
	public:
		Processor(long limit);
		~Processor();
		void do_process(SortedLimitedList<double> &list1, SortedLimitedList<double> &list2);
	};
};
