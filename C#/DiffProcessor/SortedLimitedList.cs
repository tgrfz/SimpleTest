using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DiffProcessor
{
	public class SortedLimitedList<T> where T : IComparable<T>
	{
		public class Entry
		{
			public T Value { get; internal set; }
			public Entry Previous { get; internal set; }
			public Entry Next { get; internal set; }
			public SortedLimitedList<T> List { get; internal set; }
		}

		protected Entry freePool;
		protected Entry first;
		protected Entry last;

		protected Entry allocate()
		{
			if (freePool == null)
				throw new OutOfMemoryException();
			Entry result = freePool;
			freePool = freePool.Next;

			return result;
		}

		protected void free(Entry entry)
		{
			entry.Next = freePool;
			freePool = entry;
		}

		protected void check(Entry entry)
		{
			Entry before = entry.Previous;
			if (before != null && before.Value.CompareTo(entry.Value) > 0)
				throw new Exception("List not sorted");

			Entry after = entry.Next;
			if (after != null && after.Value.CompareTo(entry.Value) < 0)
				throw new Exception("List not sorted");
		}

		public SortedLimitedList(Int32 limit)
		{
			first = null;
			last = null;
			freePool = null;
			Limit = limit;
			PerformedOperations = 0;
			Count = 0;
			for (Int32 i = 0; i < limit; ++i)
			{
				Entry current = new Entry();
				current.List = this;
				free(current);
			}
		}

		public void FromArray(T[] array)
		{
			Clear();
			for (Int32 i = 0; i < array.Length; ++i)
				AddLast(array[i]);
			PerformedOperations = 0;
		}

		public void FromList(List<T> array)
		{
			Clear();
			for (Int32 i = 0; i < array.Count; ++i)
				AddLast(array[i]);
			PerformedOperations = 0;
		}

		public override String ToString()
		{
			StringBuilder builder = new StringBuilder();
			Entry e = First;
			while (e != null)
			{
				builder.Append(e.Value);
				if (e.Next != null)
				{
					builder.Append(", ");
				}
				e = e.Next;
			}

			return builder.ToString();
		}

		public void AddAfter(Entry after, T value)
		{
			if (after == null)
				AddLast(value);
			else
			{
				Entry entry = allocate();

				entry.Value = value;
				entry.Previous = after;
				entry.Next = after.Next;
				++Count;

				if (after.Next != null)
					after.Next.Previous = entry;
				else
					last = entry;

				after.Next = entry;
				++PerformedOperations;
				check(entry);
			}
		}

		public void AddBefore(Entry before, T value)
		{
			if (before == null)
				AddFirst(value);
			else
			{
				Entry entry = allocate();

				entry.Value = value;
				entry.Previous = before.Previous;
				entry.Next = before;
				++Count;

				if (before.Previous != null)
					before.Previous.Next = entry;
				else
					first = entry;

				before.Previous = entry;
				++PerformedOperations;
				check(entry);
			}
		}

		public void AddLast(T value)
		{
			Entry entry = allocate();

			entry.Value = value;
			entry.Previous = last;
			entry.Next = null;
			++Count;

			if (last != null)
				last.Next = entry;
			else
				first = entry;

			last = entry;
			++PerformedOperations;
			check(entry);
		}

		public void AddFirst(T value)
		{
			Entry entry = allocate();

			entry.Value = value;
			entry.Previous = null;
			entry.Next = first;
			++Count;

			if (first != null)
				first.Previous = entry;
			else
				last = entry;

			first = entry;
			++PerformedOperations;
			check(entry);
		}

		public void Remove(Entry entry)
		{
			if (entry.Previous != null)
				entry.Previous.Next = entry.Next;
			else
				first = entry.Next;

			if (entry.Next != null)
				entry.Next.Previous = entry.Previous;
			else
				last = entry.Previous;

			++PerformedOperations;
			--Count;
			free(entry);
		}

		public void Clear()
		{
			Entry entry = First, next;
			while (entry != null) 
			{
				next = entry.Next;
				Remove(entry);
				entry = next;
			}
			PerformedOperations = 0;
			Count = 0;
		}

		public Int32 Count { get; private set; }
		public Int32 Limit { get; private set; }
		public Int32 PerformedOperations { get; private set; }

		public Boolean Equals(SortedLimitedList<T> list)
		{
			Entry e1 = First;
			Entry e2 = list.First;
			while (e1 != null && e2 != null)
			{
				if (e1.Value.CompareTo(e2.Value) != 0)
					return false;
				e1 = e1.Next;
				e2 = e2.Next;
			}

			return e1 == null && e2 == null;
		}

		public Entry First { get {return first; } }
		public Entry Last { get { return last; } }
	}
}
