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

int ProcessorDoProcess(PPROCESSOR processor, PSORTED_LIMITED_LIST mustBeEqualTo, const PSORTED_LIMITED_LIST expectedOutput)
{
	// TODO: make "mustBeEqualTo" list equal to "expectedOutput".
	// 0. Processor will be created once and then will be used billion times. 
	// 1. Use methods: AddFirst, AddLast, AddBefore, AddAfter, Remove to modify list.
	// 2. Do not change expectedOutput list.
	// 3. At any time number of elements in list could not exceed the "Limit". 
	// 4. "Limit" will be passed into Processor's constructor. All "mustBeEqualTo" and "expectedOutput" lists will have the same "Limit" value.
	// 5. At any time list elements must be in non-descending order.
	// 6. Implementation must perform minimal possible number of actions (AddFirst, AddLast, AddBefore, AddAfter, Remove).
	// 7. Implementation must be fast and do not allocate excess memory.
	return 0;
}