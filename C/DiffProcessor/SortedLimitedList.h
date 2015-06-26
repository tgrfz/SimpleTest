#ifndef _SORTED_LIMITED_LIST_
#define _SORTED_LIMITED_LIST_

#include "stdlib.h"
#include "stdio.h"

#if defined(__linux__)
#define INLINE                                           __inline__
#else
#define INLINE                                           __forceinline
#endif

#define SORTED_LIMITED_LIST_DEFAULT_COMPARER(x, y) ((x) == (y) ? 0 : ((x) < (y) ? -1 : +1))
#define SORTED_LIMITED_LIST_COMPARER(x, y) SORTED_LIMITED_LIST_DEFAULT_COMPARER(x, y)

#define SORTED_LIMITED_LIST_DEFINE(StructName, FunctionName, ElementType) \
SORTED_LIMITED_LIST_DEFINE_STRUCTURES(StructName, ElementType) \
SORTED_LIMITED_LIST_DEFINE_FUNCTIONS(StructName, FunctionName, ElementType) \

#define SORTED_LIMITED_LIST_DEFINE_STRUCTURES(StructName, ElementType) \
typedef struct _##StructName##_ENTRY \
{ \
	void* List; \
	struct _##StructName##_ENTRY* Previous; \
	struct _##StructName##_ENTRY* Next; \
	ElementType Value; \
} StructName##_ENTRY, *P##StructName##_ENTRY; \
typedef struct _##StructName \
{ \
	P##StructName##_ENTRY First; \
	P##StructName##_ENTRY Last; \
	long Count; \
} StructName, *P##StructName; \
typedef struct _##StructName##_PRIVATE \
{ \
	P##StructName##_ENTRY First; \
	P##StructName##_ENTRY Last; \
	long Count; \
	long PerformedOperations; \
	long Limit; \
	long ErrorCount; \
	int LastError; \
	P##StructName##_ENTRY FreePool; \
} StructName##_PRIVATE, *P##StructName##_PRIVATE; \

#define SORTED_LIMITED_LIST_DEFINE_FUNCTIONS(StructName, FunctionName, ElementType) \
static INLINE int _##FunctionName##Allocate(P##StructName##_PRIVATE list, P##StructName##_ENTRY* pentry) \
{ \
	if (list->FreePool == NULL) \
	{ \
		printf("Out of memory.\n"); \
		++list->ErrorCount; \
		list->LastError = 1; \
		return 1 /*Out of memory*/; \
	} \
	*pentry = list->FreePool; \
	list->FreePool = list->FreePool->Next; \
	return 0; \
} \
static INLINE int _##FunctionName##Free(P##StructName##_PRIVATE list, P##StructName##_ENTRY entry) \
{ \
	entry->Next = list->FreePool; \
	list->FreePool = entry; \
	return 0; \
} \
static INLINE int _##FunctionName##Check(P##StructName##_PRIVATE list, P##StructName##_ENTRY entry) \
{ \
	P##StructName##_ENTRY before = entry->Previous; \
	P##StructName##_ENTRY after = entry->Next; \
	if (before != NULL && SORTED_LIMITED_LIST_COMPARER(before->Value, entry->Value) > 0)  \
	{ \
		printf("List is not sorted.\n"); \
		++list->ErrorCount; \
		list->LastError = 2; \
		return 2 /*List not sorted*/; \
	} \
	if (after != NULL && SORTED_LIMITED_LIST_COMPARER(after->Value, entry->Value) < 0) \
	{ \
		printf("List is not sorted.\n"); \
		++list->ErrorCount; \
		list->LastError = 2; \
		return 2 /*List not sorted*/; \
	} \
	return 0; \
} \
static INLINE P##StructName FunctionName##Create(long limit) \
{ \
	P##StructName##_PRIVATE list = (P##StructName##_PRIVATE)malloc(sizeof(StructName##_PRIVATE) + sizeof(StructName##_ENTRY) * limit); \
	P##StructName##_ENTRY entries = (P##StructName##_ENTRY)((char*)list + sizeof(StructName##_PRIVATE)); \
	long i; \
	if (list == NULL) \
	{ \
		return NULL /*Failed to create a list. Probably out of memory*/; \
	} \
	list->First = NULL; \
	list->Last = NULL; \
	list->Count = 0; \
	list->PerformedOperations = 0; \
	list->Limit = limit; \
	list->ErrorCount = 0; \
	list->FreePool = NULL; \
	for (i = 0; i < limit; ++i) \
	{\
		entries[i].List = list; \
		_##FunctionName##Free(list, &entries[i]); \
	}\
	return (P##StructName)list; \
} \
static INLINE int FunctionName##Remove(P##StructName list, P##StructName##_ENTRY entry) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	if (entry->Previous != NULL) \
		entry->Previous->Next = entry->Next; \
	else \
		plist->First = entry->Next; \
	if (entry->Next != NULL) \
		entry->Next->Previous = entry->Previous; \
	else \
		plist->Last = entry->Previous; \
	++plist->PerformedOperations; \
	--plist->Count; \
	return _##FunctionName##Free(plist, entry); \
} \
static INLINE int FunctionName##Clear(P##StructName list) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	P##StructName##_ENTRY entry = plist->First, next; \
	int status; \
	while (entry != NULL) \
	{ \
		next = entry->Next; \
		if (status = FunctionName##Remove(list, entry)) \
			return status; \
		entry = next; \
	} \
	plist->PerformedOperations = 0; \
	plist->LastError = 0; \
	plist->ErrorCount = 0; \
	return 0; \
} \
static INLINE void FunctionName##Delete(P##StructName list) \
{ \
	free(list); \
} \
static INLINE int FunctionName##AddFirst(P##StructName list, ElementType value) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	P##StructName##_ENTRY entry = NULL; \
	int status = _##FunctionName##Allocate(plist, &entry); \
	if (status) \
		return status; \
	if (entry == NULL) \
	{ \
		++plist->ErrorCount; \
		plist->LastError = 1; \
		printf("Out of memory.\n"); \
		return 1 /*Out of memory*/; \
	} \
	entry->Value = value; \
	entry->Previous = NULL; \
	entry->Next = plist->First; \
	++plist->Count; \
	if (plist->First != NULL) \
		plist->First->Previous = entry; \
	else \
		plist->Last = entry; \
	plist->First = entry; \
	++plist->PerformedOperations; \
	return _##FunctionName##Check(plist, entry); \
} \
static INLINE int FunctionName##AddLast(P##StructName list, ElementType value) \
{\
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	P##StructName##_ENTRY entry = NULL; \
	int status = _##FunctionName##Allocate(plist, &entry); \
	if (status) \
		return status; \
	if (entry == NULL) \
	{ \
		++plist->ErrorCount; \
		plist->LastError = 1; \
		printf("Out of memory.\n"); \
		return 1 /*Out of memory*/; \
	} \
	entry->Value = value; \
	entry->Previous = plist->Last; \
	entry->Next = NULL; \
	++plist->Count; \
	if (plist->Last != NULL) \
		plist->Last->Next = entry; \
	else \
		plist->First = entry; \
	plist->Last = entry; \
	++plist->PerformedOperations; \
	return _##FunctionName##Check(plist, entry); \
}\
static INLINE int FunctionName##AddAfter(P##StructName list, P##StructName##_ENTRY after, ElementType value) \
{\
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	if (after == NULL) \
		return FunctionName##AddLast(list, value); \
	else \
	{ \
		P##StructName##_ENTRY entry = NULL; \
		int status = _##FunctionName##Allocate(plist, &entry); \
		if (status) \
			return status; \
		if (entry == NULL) \
		{ \
			++plist->ErrorCount; \
			plist->LastError = 1; \
			printf("Out of memory.\n"); \
			return 1 /*Out of memory*/; \
		} \
		entry->Value = value; \
		entry->Previous = after; \
		entry->Next = after->Next; \
		++plist->Count; \
		if (after->Next != NULL) \
			after->Next->Previous = entry; \
		else \
			plist->Last = entry; \
		after->Next = entry; \
		++plist->PerformedOperations; \
		return _##FunctionName##Check(plist, entry); \
	} \
}\
static INLINE int FunctionName##AddBefore(P##StructName list, P##StructName##_ENTRY before, ElementType value) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	if (before == NULL) \
		return FunctionName##AddFirst(list, value); \
	else \
	{ \
		P##StructName##_ENTRY entry = NULL; \
		int status = _##FunctionName##Allocate(plist, &entry); \
		if (status) \
			return status; \
		if (entry == NULL) \
		{ \
			++plist->ErrorCount; \
			plist->LastError = 1; \
			printf("Out of memory.\n"); \
			return 1 /*Out of memory*/; \
		} \
		entry->Value = value; \
		entry->Previous = before->Previous; \
		entry->Next = before; \
		++plist->Count; \
		if (before->Previous != NULL) \
			before->Previous->Next = entry; \
		else \
			plist->First = entry; \
		before->Previous = entry; \
		++plist->PerformedOperations; \
		return _##FunctionName##Check(plist, entry); \
	} \
} \
static INLINE int FunctionName##Equals(P##StructName list1, P##StructName list2) \
{ \
	P##StructName##_ENTRY e1 = list1->First; \
	P##StructName##_ENTRY e2 = list2->First; \
	while (e1 != NULL && e2 != NULL) \
	{ \
		if (SORTED_LIMITED_LIST_COMPARER(e1->Value, e2->Value) != 0) \
			return 0; \
		e1 = e1->Next; \
		e2 = e2->Next; \
	} \
	return e1 == NULL && e2 == NULL; \
} \
static INLINE int FunctionName##FromArray(P##StructName list, ElementType* elements, long count) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	long i; \
	int status; \
	if (status = FunctionName##Clear(list)) \
		return status; \
	for (i = 0; i < count; ++i) \
		if (status = FunctionName##AddLast(list, elements[i])) \
			return status; \
	plist->PerformedOperations = 0; \
	return 0; \
} \
static INLINE int FunctionName##Print(P##StructName list, char* elementFormat) \
{ \
	P##StructName##_ENTRY entry = list->First; \
	while (entry != NULL) \
	{ \
		printf(elementFormat, entry->Value); \
		if (entry->Next != NULL) \
			printf(", "); \
		entry = entry->Next; \
	} \
	return 0; \
} \
static INLINE long FunctionName##PerformedOperations(P##StructName list) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	return plist->PerformedOperations; \
} \
static INLINE long FunctionName##ErrorCount(P##StructName list) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	return plist->ErrorCount; \
} \
static INLINE int FunctionName##GetLastError(P##StructName list) \
{ \
	P##StructName##_PRIVATE plist = (P##StructName##_PRIVATE)list; \
	return plist->LastError; \
} \


#endif _SORTED_LIMITED_LIST_