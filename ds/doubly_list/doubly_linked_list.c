#include <stdlib.h>
#include "doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

static int print(void* data, void* param)
{

	(void)param;
	printf("%lu\n", *(size_t*)data);
	return 1;
}

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


typedef struct 
{
    size_t idNum;
} person_t;



static int is_match_func(void* data, void* param)
{
    person_t* p = (person_t*)data;

    if (p->idNum == *(size_t*)param)
    {
        return 1;
    }

    return 0;
}

int main()
{
	/*
	dlist_t *list = NULL;
	list = dlistCreate();
	assert(1==dlistIterIsEqual(dlistBegin(list), dlistEnd(list)));

	
	dlistDestroy(list);
	*/
	dlist_t *list = DListCreate();
    	dlist_t* list2 = DListCreate();
	
    
	dlist_iter_t iter = DListBegin(list);
	dlist_iter_t iter2 = DListBegin(list);
	dlist_iter_t iter3 = DListBegin(list2);
	
	int a = 5;
	char b [15] = "abc";
	int c = 100;
	size_t test1;
	person_t p1, p2, p3;
    	dlist_iter_t iter4, iter5, iter6;
	
	
	if(!(DListIterIsEqual(iter, iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	
    	if(!(DListSize(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	/*
	DListInsert(iter, &a);
	/*
	if(!(DListSize(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	/*
	if(!(*(int*)DListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListInsert(iter, b); 
	
	
	if(!(DListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(strcmp((char*)DListIterGetData(iter),"abc" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	DListInsert(iter, &c);
	
	if(!(DListSize(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(*(int*)DListIterGetData(iter) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListRemove(iter);
	
	if(!(DListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	DListDestroy(list);
	
	
	
	p1.idNum = 111;
	p2.idNum = 445;
	p3.idNum = 123;
	
	DListInsert(iter3, &p1);
    	DListInsert(iter3, &p2);
    	DListInsert(iter3, &p3);
    	
    	if(!(DListSize(list2) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
    	
	iter4 = DListBegin(list2);
	iter5 = DListEnd(list2);
	
	
	if(!(DListIterIsEqual(iter4, iter5) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	test1 = 445;
	
	iter6 = DListFind(DListBegin(list2), DListEnd(list2), is_match_func, &test1);
	
	if(!(((person_t*)DListIterGetData(iter6))->idNum == 445))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListForEach(DListBegin(list2), DListEnd(list2), print, NULL);
	*/
	DListDestroy(list2);

	
	
	
	return 0;
}
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
	dnode_t *node_temp = NULL;
	assert(list);
	node_temp = list->head;
	
	
	while(node_temp->next)
	{	
		free(node_temp->prev);
		node_temp = node_temp->next;
		
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
	new_node->prev = iter.node;
	iter.node-> next -> prev = new_node;
	
	return iter;

}

void DListRemove(dlist_iter_t iter)
{

	assert(iter.node);
	if (!iter.node->next)
		return;
	
	iter.node->next->prev = iter.node->prev;
	iter.node->prev->next = iter.node->next;
	
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

void DListPopFront(dlist_t *list)
{
	assert(list);
	
	DListRemove(DListBegin(list));

}
void DListPopBack(dlist_t *list)
{

	assert(list);
	
	
	DListRemove(DListIterPrev(DListEnd(list)));
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


