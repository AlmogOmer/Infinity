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
	void* data;
	struct SListNode* next;
};


typedef struct 
{
    size_t idNum;
} person_t;


static int is_match_func(const void* data, void* param)
{
    person_t* p = (person_t*)data;

    if (p->idNum == *(size_t*)param)
    {
        return 1;
    }

    return 0;
}

static int print(void* data, void* param)
{

	(void)param;
	printf("%lu\n", *(size_t*)data);
	return 1;
}


int main() {

    slist_t *list = SListCreate();
    slist_t* list2 = SListCreate();
	
    
	slist_iter_t iter = SListBegin(list);
	slist_iter_t iter2 = SListBegin(list);
	slist_iter_t iter3 = SListBegin(list2);
	
	int a = 5;
	char b [15] = "abc";
	int c = 100;
	size_t test1;
	person_t p1, p2, p3;
    	slist_iter_t iter4, iter5, iter6;
	
	
	if(!(SListIterIsEqual(iter, iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	
    	if(!(SListCount(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &a);
	
	if(!(SListCount(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)SListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListInsert(iter, b); /*a, b */
	
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(strcmp((char*)SListIterGetData(iter),"abc" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &c);/*a, c, b*/
	
	if(!(SListCount(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(*(int*)SListIterGetData(iter) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListRemove(iter);/*a, b*/
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	SListDestroy(list);
	
	/***********************************************************/
	
	p1.idNum = 111;
	p2.idNum = 445;
	p3.idNum = 123;
	
	SListInsert(iter3, &p1);
    	SListInsert(iter3, &p2);
    	SListInsert(iter3, &p3);
    	
    	if(!(SListCount(list2) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
    	
	iter4 = SListBegin(list2);
	iter5 = SListEnd(list2);
	
	
	if(!(SListIterIsEqual(iter4, iter5) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	test1 = 445;
	
	iter6 = SListFind(SListBegin(list2), SListEnd(list2), is_match_func, &test1);
	
	if(!(((person_t*)SListIterGetData(iter6))->idNum == 445))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListForEach(SListBegin(list2), SListEnd(list2), print, NULL);
	
	SListDestroy(list2);
	
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
	
	while(node_temp != NULL)
	{	
		temp = node_temp->next;
		free(node_temp);
		node_temp = temp;
		
	}	
	free(list);

}


void SListInsert(slist_iter_t iter, const void *item)
{
	
	snode_t *new_node = (snode_t *) malloc(sizeof(snode_t));
	
	if (NULL == new_node)
	{
		printf("insert action failed");
		exit(1);	
	}
	
	
	new_node-> data = iter.node->data;
	iter.node->data = (void *)item;
	new_node-> next = iter.node->next;
	iter.node-> next = new_node;
	

}

slist_iter_t SListBegin(slist_t *list)
{
	slist_iter_t begin_iter;
	begin_iter.node = list->head;
	return begin_iter;
}

slist_iter_t SListEnd(slist_t *list)
{
	snode_t *temp = NULL;
	slist_iter_t end_iter;
	
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
	return (iter1.node->data == iter2.node->data);
}

void SListRemove(slist_iter_t iter)
{
	snode_t *node;
	node = iter.node->next;
	iter.node->data = iter.node->next->data;
	iter.node->next = iter.node->next->next;
	
	free(node);

}

size_t SListCount(slist_t *list)
{
	size_t counter = 0;
	snode_t *node_temp;
	
	node_temp = list->head;
	
	while(node_temp->data != NULL)
	{	
		
		++counter;
		
		node_temp = node_temp->next;
		
	}	
	
	return counter;
}

void* SListIterGetData(slist_iter_t iter)
{
	return iter.node->data;
}

slist_iter_t SListIterNext(slist_iter_t iter)
{
	/*slist_iter_t iter_next;
	
	iter_next.node = */
	
	iter.node->data = iter.node->next->data;
	iter.node->next = iter.node->next->next;
	
	return iter;
}


slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param)
{
	slist_iter_t match_iter;
	
	match_iter.node = NULL;
	
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
	int counter = 0;
	while (from.node != to.node)
	{
		action_func(from.node->data, param);
		++counter;
		
		from.node = from.node->next;
	}
	
	return counter;
}






