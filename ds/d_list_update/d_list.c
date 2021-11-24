#include <stdlib.h>
#include "d_list.h"
#include <assert.h>
#include <stdio.h>



struct DListNode
{
	const void *data;
	dnode_t *next;
	dnode_t *prev;

};

struct DList
{
	
	dnode_t dummy_head;
	dnode_t dummy_tail;
	
};

/* Create new list */
dlist_t *DListCreate()
{
	
	dlist_t *new_dlist = NULL;
	new_dlist = (dlist_t *)malloc(sizeof(dlist_t));
	
	if (NULL == new_dlist)
	{
		return NULL;	
	}
	
	
	
	new_dlist->dummy_head.data = NULL;
	new_dlist->dummy_tail.data = NULL;
	
	new_dlist->dummy_head.next = &(new_dlist->dummy_tail);
	new_dlist->dummy_head.prev = NULL;
	
	
	new_dlist->dummy_tail.next = NULL;
	new_dlist->dummy_tail.prev = &(new_dlist->dummy_head);
	
	return new_dlist;


}

/* Delete the list */
void DListDestroy(dlist_t *list)
{
	
	dnode_t *node_temp = NULL;
	dnode_t *temp = NULL;
	assert(list);
	
	node_temp = list->dummy_head.next;
	
	
	while(node_temp->next != NULL)
	{	
		temp = node_temp->next;
		free(node_temp);
		node_temp = temp;
		
	}	
	

	free(list);

	
}

int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1.node && iter2.node);
	return (iter1.node == iter2.node);
	
}

dlist_iter_t DListBegin(dlist_t *list)
{
	dlist_iter_t begin_iter;
	assert(list);
	
	begin_iter.node = list->dummy_head.next;
	begin_iter.list = list;

	return begin_iter;

}

dlist_iter_t DListEnd(dlist_t *list)
{

	dlist_iter_t end_iter;
	assert(list);
	
	end_iter.node = &(list->dummy_tail); 	
	end_iter.list = list; 	
	
	return end_iter;


}


size_t DListSize(dlist_t *list)
{
	size_t Sizeer = 0;
	dnode_t *node_temp = list->dummy_head.next;
	assert(list);
	
	while(node_temp != &(list->dummy_tail))
	{	
		
		++Sizeer;
		
		node_temp = node_temp->next;
		
	}	
	
	return Sizeer;

}


dlist_iter_t DListInsert(dlist_iter_t iter, const void *item)
{
	dnode_t *new_node = (dnode_t *) malloc(sizeof(dnode_t)); 
	
	assert(item && iter.node);
	if (NULL == new_node)
	{
		return DListEnd(iter.list);	
	}
	
	new_node->data = item;
	new_node->next = iter.node;
	new_node->prev = iter.node->prev;
	
	iter.node->prev->next = new_node;
	iter.node->prev = new_node;
	
	iter.node = new_node;

	return iter;

}

void DListRemove(dlist_iter_t iter)
{
	
    	assert(iter.node);


    	if(!(iter.node -> next || iter.node -> prev))  /* Dummy nodes */
    	{
       	return;
    	}


	iter.node->prev->next = iter.node->next;
	iter.node -> next -> prev = iter.node->prev; 
	
	
        free(iter.node);


}


dlist_iter_t DListPushFront(dlist_t *list, const void *data)
{
	assert (list); 
	
	return DListInsert(DListBegin(list), data);
}

dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	assert (list);
	
	return DListInsert(DListEnd(list), data);
}	

void *DListPopFront(dlist_t *list)
{
	void *temp = NULL; 
	assert(list);
	temp = DListIterGetData(DListBegin(list));
	DListRemove(DListBegin(list));
	
	return temp;
}
void *DListPopBack(dlist_t *list)
{
	void *temp = NULL; 
	assert(list);
	temp = DListIterGetData(DListEnd(list));
	DListRemove(DListEnd(list));
	
	return temp;
}


dlist_iter_t DListIterNext(dlist_iter_t iter)
{
	assert(iter.node);
	
	iter.node = iter.node->next;
	
	return iter;
}


dlist_iter_t DListIterPrev(dlist_iter_t iter)
{

	assert(iter.node);
	
	iter.node = iter.node->prev;
	
	return iter;
}



void* DListIterGetData(dlist_iter_t iter)
{
	assert(iter.node);
	return (void *)iter.node->data;

}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match_func, void *param)
{
	dlist_iter_t match_iter;
	
	match_iter.node = NULL;
	assert(from.node && to.node);
	
	while (!DListIterIsEqual(from, to))
	{
		if(is_match_func((void *)from.node->data, param))
		{
			match_iter = from;
			break;
		}
		
		from.node = from.node->next;
	}
	
	return match_iter;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{
	assert(from.node && to.node);
	 
	while (from.node != to.node)
	{
		if(!action_func((void *)from.node->data, param))
		{
			return 0;
		}
		from.node = from.node->next;
	}
	
	return 1;
}

/* Cuts & pastes the range between begin and end into the list before 
   the element referred to by where.
   Returns iterator to the last spliced element.
   O(1) */

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin,  dlist_iter_t end)
{
	dnode_t *tmp = NULL;
	
	assert(where.node && begin.node && end.node);
	
	if (1 == DListIterIsEqual(begin, end)) 
	{
		return where;
	}
	
	end.node->prev->next = where.node;
	where.node->prev->next = begin.node;
	begin.node->prev->next = end.node;
	
	tmp = begin.node->prev;
	begin.node->prev = where.node->prev;
	where.node->prev = end.node->prev;
	end.node->prev = tmp;

	return where;
}

/*dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin, dlist_iter_t end)
{
    dlist_iter_t iter_flag;
    int flag_where_prev = 0, flag_begin_prev = 0;

    assert(where.node && begin.node && end.node);
    /* Check if we in the first node (head)/
    if(!(where.node -> prev)) /where -> prev pointing to NULL YAANI where is the first node (the head)*/
    /*{
        DListInsert(where, begin.node -> data);
        where = DListIterNext(where);
        flag_where_prev = 1;

    }
    if(!(begin.node -> prev))
    {
        iter_flag = begin;
        DListInsert(begin, end.node -> data);
        begin = DListIterNext(begin);
        flag_begin_prev = 1;
    }

    begin.node -> prev -> next = end.node -> next;
    end.node -> next -> prev = begin.node -> prev;
    where.node -> prev -> next = begin.node;
    end.node -> next = where.node;
    begin.node -> prev = where.node -> prev;
    where.node -> prev = end.node;


    if(flag_where_prev)
    {
        DListRemove(begin);
    }
    if(flag_begin_prev)
    {
        DListRemove(iter_flag);
    }

    return end;

}*/
