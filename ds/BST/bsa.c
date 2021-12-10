#include "bsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*typedef int (*compare_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*action_func_t)(void *data, const void *param);

typedef struct BST bst_t;
typedef struct BSTNode bst_node_t;

typedef struct
{
    bst_t *bst;
    bst_node_t *node;
} bst_iter_t;*/

struct BST
{
	bst_node_t *root;
	compare_func_t cmp_func;
    const void *param;
};

struct BSTNode
{
	const void *data;
	bst_node_t *left;
    bst_node_t *right;
    bst_node_t *parent;

};

static int IsLeaf(bst_node_t *node)
{
    if (node->left == NULL && node->right == NULL) 
    {    
        return 1;
    }

    return 0;
}

static bst_node_t *MinNode(bst_node_t *node)
{
    while(node && node->left)
    {
        node = node->left;
    }

    return node;
}

static void PtrSwap(const void **x, const void **y)
{
    void *tmp = NULL;
    assert(x && y);
    tmp = *(void **)x;
    *(void **)x = *(void **)y;
    *(void **)y = tmp;
}

bst_t *BstCreate(compare_func_t cmp_func, const void *param)
{
    bst_t *new_bst = NULL;
    bst_node_t *dummy_node = NULL;
 
	new_bst = (bst_t *) malloc(sizeof(bst_t));
	if (NULL == new_bst)
	{
		return NULL;
	}
	
	dummy_node = (bst_node_t *) malloc(sizeof(bst_node_t)); 
    if (NULL == dummy_node)
	{
		free(new_bst);
        return NULL ;	
	}
    
    dummy_node->data = NULL;
    dummy_node->left = NULL;
    dummy_node->right = NULL;
    dummy_node->parent = NULL;
    
    new_bst->root = dummy_node;
	new_bst->cmp_func = cmp_func;
	new_bst->param = param;
	
	return new_bst;

}


void BstDestroy(bst_t *bst)
{
   
   bst_node_t *curr_node;
   bst_node_t *temp;
   assert(bst);
   curr_node= bst->root;
   
   while(!IsLeaf(bst->root))
   {
       if (IsLeaf(curr_node))
       {
           if (curr_node == curr_node->parent->right)
           {
               curr_node->parent->right = NULL;
           }
           else
           {
               curr_node->parent->left = NULL;
           }

           temp = curr_node->parent;
           free(curr_node);
           curr_node = temp;
       }
       else if(curr_node->left)
       {
           curr_node = curr_node->left;
       }
       else
       {
           curr_node = curr_node->right;
       }
   }

	free(curr_node);
    free(bst);
}

size_t BstSize(bst_t *bst)
{
    size_t counter = 0;
    bst_iter_t from = BstBegin(bst);
    
    assert(bst);
    
    while(!BstIterIsEqual(from, BstEnd(bst)))
    {
        ++counter;
        from = BstIterNext(from);
    }
    
    return counter;
}

int BstIsEmpty(bst_t *bst)
{
    return (NULL == bst->root->data);
}

bst_iter_t BstInsert(bst_t *bst, const void *data)
{
    bst_node_t *new_node = NULL;
    bst_iter_t iter;
    bst_node_t *curr_node = bst->root;
    iter.bst = bst;
    
    new_node = (bst_node_t *) malloc(sizeof(bst_node_t)); 
	if (NULL == new_node)
	{
		return BstEnd(bst);	
	}
    
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;

    if (curr_node->data == NULL)
    {
        new_node->right =  curr_node;
        curr_node->parent = new_node;
        bst->root = new_node;
        
        iter.node = new_node;
        return iter;
    }

    while (curr_node)
    {
         
        if (curr_node->data == NULL)
        {
            curr_node->parent->right = new_node;
            new_node->parent = curr_node->parent;
            new_node->right =  curr_node;
            curr_node->parent = new_node;

            iter.node = new_node;
            return iter;
        }    
         
        if (-1 == bst->cmp_func(new_node->data, curr_node->data ,bst->param)) /*curr is bigger*/
        {
            if (curr_node->left == NULL)
            {
                curr_node->left = new_node;
                new_node->parent = curr_node;
                break;
            }
            
            curr_node = curr_node->left;
        }

        else
        {

            if (curr_node->right == NULL)
            {
                curr_node->right = new_node;
                new_node->parent = curr_node;
                break;
            }

            curr_node = curr_node->right;
        }
    }

    iter.node = new_node;
	return iter;
}

void BstRemove(bst_iter_t iter)
{

    bst_node_t *temp;
    bst_node_t *removed_node = iter.node;
    int num_of_children;

    num_of_children = (!!removed_node->left) + (!!removed_node->right);

    if (0 == num_of_children)
    {
        temp = removed_node->parent;
        if (temp->right == removed_node)
        {
            temp->right = NULL;
        }

        else
        {
            temp->left = NULL;
        }

        free(removed_node);
        return;
    }
    
    
    
    if (2 == num_of_children && removed_node->right->data !=NULL)
    {
		temp = MinNode(iter.node->right);
        PtrSwap(&removed_node->data, &temp->data);
        if (temp -> right ->data == NULL)
        {
            temp->right->parent = temp->parent;
            temp->parent->right = temp->right;

        }
        free(temp);
        return;

	}

	if (1 == num_of_children || removed_node->right->data == NULL)
	{
		if (removed_node->left && removed_node->right->data == NULL)
        {
            removed_node->left->parent = removed_node->parent;
            removed_node->right->parent = removed_node->left;
        }
        
        else if (removed_node->right && removed_node->left == NULL)
        {
            removed_node->right->parent = removed_node->parent;
        }
        
        else if (removed_node->left && removed_node->right == NULL)
        {
            removed_node->left->parent = removed_node->parent;
        }
	
    
        free(removed_node);
        return;
    
    }
    
}

bst_iter_t BstBegin(bst_t *bst)
{
    bst_iter_t iter_begin;
    bst_node_t *temp;
    
    iter_begin.bst = bst;
    temp = bst->root;
    
    while (temp->left)
    {
        temp = temp->left;
    }

    iter_begin.node = temp;
    return iter_begin;
}

bst_iter_t BstEnd(bst_t *bst)
{
    bst_iter_t iter_end;
    bst_node_t *temp;
    
    iter_end.bst = bst;
    temp = bst->root;
    
    while (temp->right)
    {
        temp = temp->right;
    }

    iter_end.node = temp;
    return iter_end;
}

bst_iter_t BstIterNext(bst_iter_t iter)
{
    bst_iter_t iter_next;
    bst_node_t *temp;

    iter_next.bst = iter.bst;
    temp = iter.node;
    
    if (BstIterIsEqual(iter,BstIterPrev(BstEnd(iter.bst))))
    {
        return (BstEnd(iter.bst));
    }
    
    
    if (temp->right)
    {
        temp = temp->right;
        while(temp->left)
        {
            temp = temp->left;
        }
        
    }

    else
    {
        while(temp->parent)
        {
            if ( 1 == iter.bst->cmp_func(temp->parent, temp ,iter.bst->param))
            {
                temp = temp->parent;
                break;
            }
            temp = temp->parent;
        }
        
  
    }
    iter_next.node = temp;
    return iter_next;
}
bst_iter_t BstIterPrev(bst_iter_t iter)
{
    bst_iter_t iter_prev;
    bst_node_t *temp;

    iter_prev.bst = iter.bst;
    temp = iter.node;
    
    if (BstIterIsEqual(iter,BstEnd(iter.bst)))
    {
        iter.node = iter.node->parent;
        return (iter);
    }
    
    if (temp->left)
    {
        while(temp->left)
        {
            temp = temp->right;
        }
        
    }

    else
    {
        while(1 == iter.bst->cmp_func(temp,temp->parent, iter.bst->param))
        {
            temp = temp->parent;
        }
        
  
    }
    iter_prev.node = temp;
    return iter_prev;
}

int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(iter1.node && iter2.node);
    return iter1.node == iter2.node;
}

void *BstIterGetData(bst_iter_t iter)
{
    return((void*)iter.node->data);
}

bst_iter_t BstFind(bst_t *bst, const void *data)
{
    int result;
    bst_node_t *node = NULL;
    bst_iter_t iter_result;

    assert(bst && data);
    iter_result.bst = bst;

   
    node = bst->root;

    while (node->data != NULL)
    {
        result = bst->cmp_func(data, node->data, bst->param);

        if (0 == result)       /* data exist in tree */
        {
            iter_result.node = node;
            return iter_result;   
        }

        else if (1 == result)   /* if result equals 1- go RIGHT, else go LEFT */
        {
            node = node->right;
        }

        else
        {
            node = node->left;
        }
 
    }

    iter_result = BstEnd(bst);
    return iter_result;     /* data does not exist in tree */
}
   


int BstForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, const void *param)
{

    for (; !BstIterIsEqual(from, to); from = BstIterNext(from))
    {
        if (!action_func(BstIterGetData(from), param))
        {
            return 0;
        }
    }

    return 1;
}





