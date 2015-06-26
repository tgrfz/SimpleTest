using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DiffProcessor;

namespace SimpleTest
{
	class Program
	{
		static Processor diffProcessor = new Processor(10);
		static SortedLimitedList<Double> sortedList1 = new SortedLimitedList<Double>(10);
		static SortedLimitedList<Double> sortedList2 = new SortedLimitedList<Double>(10);
		static SortedLimitedList<Double> sortedList1_ = new SortedLimitedList<Double>(10);
		static SortedLimitedList<Double> sortedList2_ = new SortedLimitedList<Double>(10);
		static Int64 test = 0;
		static void DoTest(Int32 operations)
		{
			try
			{
				diffProcessor.DoProcess(sortedList1, sortedList2);
				if (!sortedList1.Equals(sortedList2) || !sortedList1.Equals(sortedList2_) || sortedList1.PerformedOperations != operations)
				{
					Console.WriteLine("Test case: " + ++test + " Failed. Inputs: mustBeEqual: [" + sortedList1_ + "] etalon: [" + sortedList2_ + "]");
					Console.WriteLine("Your output " + sortedList1);
					Console.WriteLine("Performed operations: " + sortedList1.PerformedOperations + ", expected " + operations);
					Console.WriteLine();
				}
				else
				{
					Console.WriteLine("Test case: " + ++test + " Succeed. Inputs: mustBeEqual: [" + sortedList1_ + "] etalon: [" + sortedList2_ + "]");
					Console.WriteLine();
				}
			} 
			catch (Exception)
			{
				Console.WriteLine("Test case: " + ++test + " Exception. Inputs: mustBeEqual: [" + sortedList1_ + "] etalon: [" + sortedList2_ + "]");
				Console.WriteLine();
			}
		}

		static void Test(Double[] array1, Double[] array2, Int32 operations)
		{
			sortedList1.FromArray(array1);
			sortedList2.FromArray(array2);
			sortedList1_.FromArray(array1);
			sortedList2_.FromArray(array2);
			DoTest(operations);
		}

		static void Test(List<Double> list1, List<Double> list2, Int32 operations)
		{
			sortedList1.FromList(list1);
			sortedList2.FromList(list2);
			sortedList1_.FromList(list1);
			sortedList2_.FromList(list2);
			DoTest(operations);
		}


		static void Main(String[] args)
		{
			Double[] needToBeEqual_0 = { 0, 1, 2, 3, 4, 6, 7 };
			Double[] etalon_0 = { 0, 1, 2, 3, 4, 5, 6, 7 };
			Test(needToBeEqual_0, etalon_0, 1);

			Double[] needToBeEqual_1 = { 0, 1, 2, 3, 4, 6, 7 };
			Double[] etalon_1 = { 1, 2, 3, 3 };
			Test(needToBeEqual_1, etalon_1, 5);

			Double[] needToBeEqual_2 = { 0 };
			Double[] etalon_2 = { 7 };
			Test(needToBeEqual_2, etalon_2, 2);

			Double[] needToBeEqual_3 = { 0, 1, 1, 1, 1, 1, 1 };
			Double[] etalon_3 = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
			Test(needToBeEqual_3, etalon_3, 17);

			Double[] needToBeEqual_4 = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
			Double[] etalon_4 = { 0, 2, 2, 2, 2, 2, 2, 2, 2, 3 };
			Test(needToBeEqual_4, etalon_4, 16);

			Double[] needToBeEqual_5 = { 0, 1, 2, 3, 4, 6, 7 };
			Double[] etalon_5 = { };
			Test(needToBeEqual_5, etalon_5, 7);

			Double[] needToBeEqual_6 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
			Double[] etalon_6 = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			Test(needToBeEqual_6, etalon_6, 2);

			Double[] needToBeEqual_7 = { 0, 0};
			Double[] etalon_7 = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
			Test(needToBeEqual_7, etalon_7, 10);
		}
	}
}
