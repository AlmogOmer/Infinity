#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "singly_list.h"

struct SList 
{
	snode_t *head;
};

struct SListNode {
	const void* data;
	struct SListNode* next;
};

static int count_func(void* data, void* param)
{

	if((int*)data)
	{
		++*(int*)param;
		return 1;
	}
	return 0;
}


/* Create new list */
slist_t *SListCreate(void)
{
	slist_t *new_list = NULL;
	snode_t *dummy_node = NULL;
	new_list = (slist_t *)malloc(sizeof(slist_t));
	
	if (NULL == new_list)
	{
		return NULL;	
	}
	
	dummy_node = (snode_t *) malloc(sizeof(snode_t));
	
	if (NULL == dummy_node)
	{
		return NULL;	
	}
	
	dummy_node-> data = NULL;
	dummy_node-> next = NULL;
	new_list-> head = dummy_node;
	
	
	
	return new_list;

}

/* Delete the list */
void SListDestroy(slist_t *list)
{
	
	snode_t *node_temp;
	snode_t *temp;
	node_temp = list->head;
	assert(list);
	
	while(node_temp != NULL)
	{	
		temp = node_temp->next;
		free(node_temp);
		node_temp = temp;
		
	}	
	
	free(node_temp);
	free(list);

}


slist_iter_t SListInsert(slist_iter_t iter, const void *item)
{
	
	snode_t *new_node = (snode_t *) malloc(sizeof(snode_t));
	assert(item && iter.node);
	
	if (NULL == new_node)
	{
		return iter;	
	}
	
	
	new_node-> data = iter.node->data;
	iter.node->data = item;
	new_node-> next = iter.node->next;
	iter.node-> next = new_node;
	
	return iter;
}

slist_iter_t SListBegin(slist_t *list)
{
	slist_iter_t begin_iter;
	assert(list);
	
	begin_iter.node = list->head;
	

	return begin_iter;
}

slist_iter_t SListEnd(slist_t *list)
{
	snode_t *temp = NULL;
	slist_iter_t end_iter;
	assert(list);
	
	temp = list->head;
	while(temp->next != NULL)
	{	
		temp = temp->next;
	}
	
	end_iter.node = temp; 	
	
	return end_iter;
}

int SListIterIsEqual(slist_iter_t iter1, slist_iter_t iter2)
{
	assert(iter1.node && iter2.node);
	return (iter1.node == iter2.node);
}

void SListRemove(slist_iter_t iter)
{
	snode_t *node;
	assert(iter.node);
	if (!iter.node->next)
		return;
	node = iter.node->next;
	iter.node->data = iter.node->next->data;
	iter.node->next = iter.node->next->next;
	
	free(node);

}

size_t SListCount(slist_t *list)
{
	/*size_t counter = 0;
	snode_t *node_temp = list->head ;
	assert(list);
	
	while(node_temp->data != NULL)
	{	
		
		++counter;
		
		node_temp = node_temp->next;
		
	}	
	
	return counter;*/
	
	size_t counter = 0;
	
	assert(list);
	
	SListForEach(SListBegin(list), SListEnd(list), count_func, &counter);
	
	return counter;
	
	
}

void* SListIterGetData(slist_iter_t iter)
{
	assert(iter.node);
	return (void *)iter.node->data;
}

slist_iter_t SListIterNext(slist_iter_t iter)
{
	
	assert(iter.node);
	if (!iter.node->next)
		return iter;
	iter.node = iter.node->next;
	
	return iter;
}


slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param)
{
	slist_iter_t match_iter;
	
	match_iter.node = NULL;
	assert(from.node && to.node);
	
	while (!SListIterIsEqual(from, to))
	{
		if(is_match_func(from.node->data, param))
		{
			match_iter = from;
			break;
		}
		
		from.node = from.node->next;
	}
	
	return match_iter;
	
}

int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param)
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






