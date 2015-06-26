#include "../DiffProcessor/DiffProcessor.h"

PPROCESSOR diffProcessor;
PSORTED_LIMITED_LIST sortedList1; 
PSORTED_LIMITED_LIST sortedList2;
PSORTED_LIMITED_LIST sortedList1_;
PSORTED_LIMITED_LIST sortedList2_;
long long test = 0;

void DoTest(long operations)
{
	int status;
	if (status = ProcessorDoProcess(diffProcessor, sortedList1, sortedList2) || SortedLimitedListErrorCount(sortedList1) > 0)
	{
		printf("Test case: %d Exception. Status: %d Inputs: mustBeEqual: [", ++test, SortedLimitedListGetLastError(sortedList1));
		SortedLimitedListPrint(sortedList1_, "%0.1lf");
		printf("] expected: [");
		SortedLimitedListPrint(sortedList2_, "%0.1lf");
		printf("]\n\n");
	}
	else if (!SortedLimitedListEquals(sortedList1, sortedList2) || !SortedLimitedListEquals(sortedList1, sortedList2_) || SortedLimitedListPerformedOperations(sortedList1) != operations)
	{
		int a = SortedLimitedListEquals(sortedList1, sortedList2);
		int b = SortedLimitedListEquals(sortedList1, sortedList2_);
		printf("Test case: %d Error. Inputs: mustBeEqual: [", ++test);
		SortedLimitedListPrint(sortedList1_, "%0.1lf");
		printf("] expected: [");
		SortedLimitedListPrint(sortedList2_, "%0.1lf");
		printf("]\n");
		printf("Your output ");
		SortedLimitedListPrint(sortedList1, "%0.1lf");
		printf("\n");
		printf("Performed operations: %d, expected %d\n\n", SortedLimitedListPerformedOperations(sortedList1), operations);
	}
	else
	{
		printf("Test case: %d Success. Inputs: mustBeEqual: [", ++test);
		SortedLimitedListPrint(sortedList1_, "%0.1lf");
		printf("] expected: [");
		SortedLimitedListPrint(sortedList2_, "%0.1lf");
		printf("]\n\n");
	}
}

void Test(double* array1, long arraySize1, double* array2, long arraySize2, long operations)
{
	SortedLimitedListFromArray(sortedList1, array1, arraySize1);
	SortedLimitedListFromArray(sortedList2, array2, arraySize2);
	SortedLimitedListFromArray(sortedList1_, array1, arraySize1);
	SortedLimitedListFromArray(sortedList2_, array2, arraySize2);
	DoTest(operations);
}

int main(int argc, char **argv)
{
	diffProcessor = ProcessorCreate();
	sortedList1 = SortedLimitedListCreate(10);
	sortedList2 = SortedLimitedListCreate(10);
	sortedList1_ = SortedLimitedListCreate(10);
	sortedList2_ = SortedLimitedListCreate(10);

	{
		double needToBeEqual_0[] = { 0, 1, 2, 3, 4, 6, 7 };
		double expected_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		Test(needToBeEqual_0, sizeof(needToBeEqual_0) / sizeof(double), expected_0, sizeof(expected_0) / sizeof(double), 1);
	}

	{
		double needToBeEqual_1[] = { 0, 1, 2, 3, 4, 6, 7 };
		double expected_1[] = { 1, 2, 3, 3 };
		Test(needToBeEqual_1, sizeof(needToBeEqual_1) / sizeof(double), expected_1, sizeof(expected_1) / sizeof(double), 5);
	}

	{
		double needToBeEqual_2[] = { 0 };
		double expected_2[] = { 7 };
		Test(needToBeEqual_2, sizeof(needToBeEqual_2) / sizeof(double), expected_2, sizeof(expected_2) / sizeof(double), 2);
	}

	{
		double needToBeEqual_3[] = { 0, 1, 1, 1, 1, 1, 1 };
		double expected_3[] = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
		Test(needToBeEqual_3, sizeof(needToBeEqual_3) / sizeof(double), expected_3, sizeof(expected_3) / sizeof(double), 17);
	}

	{
		double needToBeEqual_4[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
		double expected_4[] = { 0, 2, 2, 2, 2, 2, 2, 2, 2, 3 };
		Test(needToBeEqual_4, sizeof(needToBeEqual_4) / sizeof(double), expected_4, sizeof(expected_4) / sizeof(double), 16);
	}

	{
		double needToBeEqual_5[] = { 0, 1, 2, 3, 4, 6, 7 };
		Test(needToBeEqual_5, sizeof(needToBeEqual_5) / sizeof(double), NULL, 0, 7);
	}

	{
		double needToBeEqual_6[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
		double expected_6[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		Test(needToBeEqual_6, sizeof(needToBeEqual_6) / sizeof(double), expected_6, sizeof(expected_6) / sizeof(double), 2);
	}

	{
		double needToBeEqual_7[] = { 0, 0 };
		double expected_7[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		Test(needToBeEqual_7, sizeof(needToBeEqual_7) / sizeof(double), expected_7, sizeof(expected_7) / sizeof(double), 10);
	}

	ProcessorDelete(diffProcessor);
}
