#pragma once

#include "stdafx.h"
#include "Processor.h"

namespace DiffProcessor
{
	Processor::Processor(long limit)
	{
		// TODO: initialization.
	}
	Processor::~Processor()
	{
		// TODO: Free resources.
	}

	void Processor::do_process(SortedLimitedList<double> &must_be_equal_to, SortedLimitedList<double> &etalon)
	{
		// TODO: make "must_be_equal_to" list equal to "etalon".
		// 0. Processor will be created once and then will be used billion times. 
		// 1. Use methods: AddFirst, AddLast, AddBefore, AddAfter, Remove to modify list.
		// 2. Do not change etalon list.
		// 3. At any time number of elements in list could not exceed the "Limit". 
		// 4. "Limit" will be passed into Processor's constructor. All "must_be_equal_to" and "etalon" lists will have the same "Limit" value.
		// 5. At any time list elements must be in non-descending order.
		// 6. Implementation must perform minimal possible number of actions (AddFirst, AddLast, AddBefore, AddAfter, Remove).
		// 7. Implementation must be fast and do not allocate excess memory.
	}
};
