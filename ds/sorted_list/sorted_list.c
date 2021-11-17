#include<stdio.h>
#include<assert.h>
#include <stdlib.h>
#include"sorted_list.h"
#include "../doubly_list/doubly_linked_list.h"

struct SortedList 
{
	dlist_t *dlist;
	is_before_func_t IsBefore;
	void *param;

};


sorted_list_t *SortedListCreate(is_before_func_t is_before, void *param)
{

	sorted_list_t *new_list = NULL;
	
	assert(is_before);
	
	new_list = (sorted_list_t *) malloc(sizeof(sorted_list_t));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	new_list->dlist = DListCreate();
	if (NULL == new_list->dlist)
	{
		free(new_list);
		return NULL;
	}
	
	new_list->IsBefore = is_before;
	new_list->param = param;
	
	return new_list;

}

/* Delete the list */
void SortedListDestroy(sorted_list_t *list)
{
	assert(list);
	
	DListDestroy(list->dlist);
	free(list);
}

sorted_list_iter_t SortedListBegin(sorted_list_t *list)
{
	sorted_list_iter_t iter;
	assert(list);
	
	iter.list = list;
	iter.d_list_iter =  DListBegin(list->dlist);
	return iter;

}
sorted_list_iter_t SortedListEnd(sorted_list_t *list)
{
	
	sorted_list_iter_t iter;
	assert(list);
	
	iter.list = list;
	iter.d_list_iter =  DListEnd(list->dlist);
	return iter;

}

sorted_list_iter_t SortedListIterNext(sorted_list_iter_t iter)
{
	
	assert(iter.d_list_iter.node);
	
	iter.d_list_iter = DListIterNext(iter.d_list_iter);
	return iter;

}
sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t iter)
{
	assert(iter.d_list_iter.node);
	
	iter.d_list_iter = DListIterPrev(iter.d_list_iter);
	return iter;

}
int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	assert(iter1.d_list_iter.node && iter2.d_list_iter.node);
	
	return DListIterIsEqual(iter1.d_list_iter, iter2.d_list_iter);

}
void* SortedListIterGetData(sorted_list_iter_t iter)
{
	assert(iter.d_list_iter.node);
	
	return DListIterGetData(iter.d_list_iter);

}

size_t SortedListSize(sorted_list_t *list)
{
	assert(list);
	
	return DListSize(list->dlist);
}

/* insert item to the list O(n) */
sorted_list_t *SortedListInsert(sorted_list_t *list, const void *item)
{
	sorted_list_iter_t runner;
	
	assert(list);
	runner = SortedListBegin(list);
	
	

	/*going through the list until the new data is not less then the current*/
	while (0 == SortedListIterIsEqual(runner, SortedListEnd(list)))
	{
		if (0 == list->IsBefore(SortedListIterGetData(runner), item, list->param))
		{
			break;
		}
		
		runner =SortedListIterNext(runner);
	}
	
	DListInsert(runner.d_list_iter, item);
	
	return list;

}


/* Remove item from the list */
void SortedListRemove(sorted_list_iter_t which)
{
	assert(which.d_list_iter.node);
	
	DListRemove(which.d_list_iter);

}

sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, const void *what)
{

	sorted_list_iter_t match_iter;
	
	
	match_iter.d_list_iter.node = NULL;
	match_iter.list = from.list;
	assert(from.d_list_iter.node && to.d_list_iter.node);
	
	while (!SortedListIterIsEqual(from, to))
	{
		if (0 == from.list->IsBefore(what, SortedListIterGetData(from), from.list->param))
		
		{
			if (0 == from.list->IsBefore(SortedListIterGetData(from), what, from.list->param))
			{
				match_iter = from;
				break;
			}	
			
		}
		
		else 
		{
			printf("item was not found");
			break;
		
		}
		
		from = SortedListIterNext(from);
	}
	
	return match_iter;


}

	
/*sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, match_func_t is_match_func, void *param); */

int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, act_func_t action_func, void *param)
{

	assert(from.d_list_iter.node && to.d_list_iter.node);
	 
	return DListForEach(from.d_list_iter, to.d_list_iter, action_func, param);

}



/* Merge lists */ 
sorted_list_t *SortListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{

	sorted_list_iter_t from_runner ;
	assert(dest_list && src_list);
	
	from_runner = SortedListBegin(src_list);
	/* traverse the from list */
	while (!SortedListIterIsEqual(from_runner, SortedListEnd(src_list)))
	{
		
		SortedListInsert(dest_list, SortedListIterGetData(from_runner));
		from_runner = SortedListIterNext(from_runner);
	
	}
	SortedListDestroy(src_list);
	return dest_list;	
}







