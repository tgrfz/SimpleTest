#pragma once

#include "SortedLimitedList.h"

namespace DiffProcessor
{
	class Processor
	{
	public:
		Processor(long limit);
		~Processor();
		void do_process(SortedLimitedList<double> &must_be_equal_to, const SortedLimitedList<double> &expected_output);
	};
};
