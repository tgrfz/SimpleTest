#ifndef _PROCESSOR_
#define _PROCESSOR_

#include "SortedLimitedList.h"

typedef struct _PROCESSOR
{
	/* Fill in with necessary data */
	char dummy;
} PROCESSOR, *PPROCESSOR;

SORTED_LIMITED_LIST_DEFINE(SORTED_LIMITED_LIST, SortedLimitedList, double);

PPROCESSOR ProcessorCreate();
int ProcessorDoProcess(PPROCESSOR processor, PSORTED_LIMITED_LIST mustBeEqualTo, PSORTED_LIMITED_LIST etalon);
void ProcessorDelete(PPROCESSOR processor);

#endif _PROCESSOR_