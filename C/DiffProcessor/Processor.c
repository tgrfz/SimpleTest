#include "DiffProcessor.h"

PPROCESSOR ProcessorCreate(long limit)
{
	// TODO: initialization.
	return NULL;
}

void ProcessorDelete(PPROCESSOR processor)
{
	// TODO: Free resources.
}

int ProcessorDoProcess(PPROCESSOR processor, PSORTED_LIMITED_LIST mustBeEqualTo, PSORTED_LIMITED_LIST etalon)
{
	// TODO: make "mustBeEqualTo" list equal to "etalon".
	// 0. Processor will be created once and then will be used billion times. 
	// 1. Use methods: AddFirst, AddLast, AddBefore, AddAfter, Remove to modify list.
	// 2. Do not change etalon list.
	// 3. At any time number of elements in list could not exceed the "Limit". 
	// 4. "Limit" will be passed into Processor's constructor. All "mustBeEqualTo" and "etalon" lists will have the same "Limit" value.
	// 5. At any time list elements must be in non-descending order.
	// 6. Implementation must perform minimal possible number of actions (AddFirst, AddLast, AddBefore, AddAfter, Remove).
	// 7. Implementation must be fast and do not allocate excess memory.
	PSORTED_LIMITED_LIST_ENTRY t;
	PSORTED_LIMITED_LIST_ENTRY e1 = mustBeEqualTo->First;
	PSORTED_LIMITED_LIST_ENTRY e2 = etalon->First;
	while (e1 != NULL)
	{
		if (e2 != NULL)
		{
			if (e1->Value < e2->Value)
			{
				t = e1;
				e1 = e1->Next;
				SortedLimitedListRemove(mustBeEqualTo, t);
			}
			else if (e1->Value > e2->Value)
				e2 = e2->Next;
			else
			{
				e1 = e1->Next;
				e2 = e2->Next;
			}
		}
		else
		{
			t = e1;
			e1 = e1->Next;
			SortedLimitedListRemove(mustBeEqualTo, t);
		}
	}

	e1 = mustBeEqualTo->First;
	e2 = etalon->First;

	while (e2 != NULL)
	{
		if (e1 != NULL)
		{
			if (e1->Value > e2->Value)
			{
				SortedLimitedListAddBefore(mustBeEqualTo, e1, e2->Value);
				e2 = e2->Next;
			}
			else
			{
				e1 = e1->Next;
				e2 = e2->Next;
			}
		}
		else
		{
			SortedLimitedListAddLast(mustBeEqualTo, e2->Value);
			e2 = e2->Next;
		}
	}

	return 0;
}