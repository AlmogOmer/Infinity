#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#include <stdlib.h>
#include "common_types.h"

typedef struct DList dlist_t;
typedef struct DListNode dnode_t;


typedef struct
{
	dnode_t* node;
} dlist_iter_t;


/* Create new list */
extern dlist_t *DListCreate();

/* Delete the list */
extern void DListDestroy(dlist_t *list);

extern dlist_iter_t DListBegin(dlist_t *list);
extern dlist_iter_t DListEnd(dlist_t *list);
extern dlist_iter_t DListInsert(dlist_iter_t iter, const void *item);
extern void DListRemove(dlist_iter_t iter);
extern size_t DListCount(dlist_t *list);

extern dlist_iter_t DListIterNext(dlist_iter_t iter);
extern dlist_iter_t DListIterPrev(dlist_iter_t iter);
extern int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2);
extern void* DListIterGetData(dlist_iter_t iter);

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, cmp_func_t cmp_func, const void *param, const void *data);
int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, const void *param);



/* ----------- UPDATE -------------- */
size_t DListSize(dlist_t *list);

dlist_iter_t DListPushFront(dlist_t *list, const void *data);
dlist_iter_t DListPushBack(dlist_t *list, const void *data);
void* DListPopFront(dlist_t *list);
void* DListPopBack(dlist_t *list);

/* Cuts & pastes the range between begin and end into the list before 
   the element referred to by where.
   Returns iterator to the last spliced element.
   O(1) */

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin, dlist_iter_t end);



#endif

