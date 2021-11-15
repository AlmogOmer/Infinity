#include <stdlib.h>
#include "doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>


struct DList
{
	dnode_t *head;
	
};

struct DListNode
{
	const void*data;
	struct DListNode *next;
	struct DListNode *prev;

};



/* Create new list */
dlist_t *DListCreate()
{
	dlist_t *new_dlist = NULL;
	dnode_t *dummy_node = NULL;
	new_dlist = (dlist_t *)malloc(sizeof(dlist_t));
	
	if (NULL == new_dlist)
	{
		return NULL;	
	}
	
	dummy_node = (dnode_t *) malloc(sizeof(dnode_t));
	
	if (NULL == dummy_node)
	{
		return NULL;	
	}
	
	dummy_node-> data = NULL;
	dummy_node-> next = NULL;
	dummy_node-> prev = NULL;
	
	new_dlist-> head = dummy_node;

	
	
	return new_dlist;


}

/* Delete the list */
void DListDestroy(dlist_t *list)
{
	
	dnode_t *node_temp;
	dnode_t *temp;
	assert(list);
	
	node_temp = list->head;
	
	
	while(node_temp != NULL)
	{	
		temp = node_temp->next;
		free(node_temp);
		node_temp = temp;
		
	}	
	
	free(node_temp);
	free(list);

	
}

int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(iter1.node && iter2.node);
	return (iter1.node->next == iter2.node->next);
	
}

dlist_iter_t DListBegin(dlist_t *list)
{
	dlist_iter_t begin_iter;
	assert(list);
	
	begin_iter.node = list->head;
	

	return begin_iter;

}

dlist_iter_t DListEnd(dlist_t *list)
{

	dnode_t *temp = NULL;
	dlist_iter_t end_iter;
	assert(list);
	
	temp = list->head;
	while(temp->next != NULL)
	{	
		temp = temp->next;
	}
	
	end_iter.node = temp; 	
	
	return end_iter;


}


size_t DListSize(dlist_t *list)
{
	size_t Sizeer = 0;
	dnode_t *node_temp = list->head ;
	assert(list);
	
	while(node_temp->data != NULL)
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
		return iter;	
	}
	
	new_node-> data = iter.node->data;
	iter.node->data = item;
	
	new_node-> next = iter.node->next;
	iter.node-> next = new_node;
	
	new_node->prev = iter.node;
	if (new_node->next != NULL)  /*checks if this is not the first item in list*/
	{
		new_node-> next ->prev = new_node;
	}
	return iter;

}

void DListRemove(dlist_iter_t iter)
{
	
	dnode_t *temp;
	assert(iter.node);
	
	temp = iter.node->next;
	
	if (!iter.node->next)
	{
		return;
	}
	
	if (!iter.node->prev)
	{
		iter.node->data = temp ->data;
		iter.node->next = temp->next;
		free(temp);
	}
	
	else
	{
		iter.node->next->prev = iter.node->prev;
		iter.node->prev->next = iter.node->next;
		free(iter.node);
	}

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
	temp = DListIterGetData(DListIterPrev(DListEnd(list)));
	DListRemove(DListIterPrev(DListEnd(list)));
	
	return temp;
}


dlist_iter_t DListIterNext(dlist_iter_t iter)
{
	assert(iter.node);
	if (!iter.node->next)
		return iter;
	iter.node = iter.node->next;
	
	return iter;
}


dlist_iter_t DListIterPrev(dlist_iter_t iter)
{

	assert(iter.node);
	if (!iter.node->prev)
		return iter;
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
   O(1) 

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t begin,  dlist_iter_t end);*/


