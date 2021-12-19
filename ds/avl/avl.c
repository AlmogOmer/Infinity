#include "avl.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

typedef struct avl_node node_t;

struct AVL
{
	node_t *root;
	compare_func_t cmp_func;
	const void *param;
};

struct avl_node
{
	const void *data;
	node_t *right;
	node_t *left;
	size_t height;
};

static size_t Height(node_t *node)
{
	if (node)
	{
		return node->height;
	}
	
	return 0;
}


static node_t *CreateNode(const void *data)
{
	node_t *node = (node_t *) malloc(1 * sizeof(node_t));
	if (!node)
	{
		return NULL;
	}

	node->data = data;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;

	return node;
}

/* complexity O(1) */
/* Create new AVL */
avl_t *AvlCreate(compare_func_t cmp_func, const void *param)
{
    avl_t *tree = (avl_t *) malloc(1 *sizeof(avl_t));
	if(!tree)
	{
		return NULL;
	}

	tree->root = NULL;
	tree->cmp_func = cmp_func;
	tree->param = param;

	return tree;
}

/* recursive post order traversal for freeing all allocated nodes */
static void DestroyRec(node_t *root)
{
	if (NULL == root)
	{
		return;
	}

	DestroyRec(root->left);
	DestroyRec(root->right);
	free(root);
}

/* complexity O(n) */
/* Destroy AVL*/
void AvlDestroy(avl_t *avl)
{
    DestroyRec(avl->root);
	free(avl);
}

/* complexity O(1) */
/* Height of root */
size_t AvlHeight(const avl_t *avl)
{
    if(avl->root)
    {
        return avl->root->height;
    }

    return 0;
}

/* recursive count for number of nodes in tree */
static size_t AvlSizeRec(node_t *root)
{
	if (NULL == root)
	{
		return 0;
	}

	return 1 + AvlSizeRec(root->left) + AvlSizeRec(root->right);
}

/* complexity O(n) */
/* Size of AVL*/
size_t AvlSize(const avl_t *avl)
{
    return AvlSizeRec(avl->root);
}

/* complexity O(1) */
/* If AVL is Empty return 1  */
int AvlIsEmpty(const avl_t *avl)
{
    return (NULL == avl->root);
}

/* recursive function for insertion of new node */
static node_t *InsertRec(node_t *root, node_t *new_node, compare_func_t cmp_func, const void *param)
{
	int result = 0;
	
	if (NULL == root)
	{
		return new_node;
	}

	result = cmp_func(root->data, new_node->data, param);

	assert(0 != result); /*check if already in tree*/

	if (result < 0)
	{
		root->right = InsertRec(root->right, new_node, cmp_func, param);
	}
	else
	{
		root->left = InsertRec(root->left, new_node, cmp_func, param);
	}

	return root; 
}

/* complexity O(logn) */
/* Insert a new node - 0 if succes, 1 fail */
int AvlInsert(avl_t *avl, const void *data)
{
    node_t *new_node = CreateNode(data);
	if (!new_node)
	{
		return 1;
	}

	avl->root = InsertRec(avl->root, new_node, avl->cmp_func, avl->param);
	return 0;	
}


/* recursive function that find the minimum */
static node_t *FindMin(node_t *root)
{
	if (root->left)
	{
		return FindMin(root->left);
	}
	
	return root;
}


/* recursive function that find a node and remove it */
static node_t *RemoveRec(node_t *root, const void *data, compare_func_t cmp_func, const void *param)
{
	int cmp_result = 0;
	node_t *chlid_left = 0;
	node_t *chlid_right = 0;
	node_t *next = NULL;

	if (NULL == root)
	{
		return NULL;
	}

	cmp_result = cmp_func(root->data, data, param);

	if (cmp_result < 0)
	{
		root->right = RemoveRec(root->right, data, cmp_func, param);
		return root; 
	}
	if (cmp_result > 0)
	{
		root->left = RemoveRec(root->left, data, cmp_func, param);
		return root;
	}

	chlid_left = root->left;
	chlid_right = root->right;
	free(root);

	if (NULL == chlid_right)
	{
		return chlid_left;
	}

	next = FindMin(chlid_right);
	next->right = chlid_right; /*need to fix*/
	next->left = chlid_left;

	return next;
}

/* complexity O(logn) */
/* Remove a node  */
void AvlRemove(avl_t *avl, const void *data)
{
	avl->root = RemoveRec(avl->root, data, avl->cmp_func, avl->param);

	return;
} 

/* recursive function that find node */
static const void *FindRec(node_t *root, const void *data_to_match, compare_func_t cmp_func, const void *param)
{
	int result = 0;
	
	if (NULL == root)
	{
		return NULL;
	}

	result = cmp_func(root->data, data_to_match, param);

	if (result < 0)
	{
		return FindRec(root->right, data_to_match, cmp_func, param);
	}
	else if (result > 0)
	{
		return FindRec(root->left, data_to_match, cmp_func, param);
	}

	return root->data;
}

/* complexity O(logn) */
/* Find a node in AVL  */
const void *AvlFind(avl_t *avl, const void *data)
{
    return FindRec(avl->root, data, avl->cmp_func, avl->param);
}


static int InOrderTraverse(node_t *root, action_func_t act_func, const void *param)
{
	if (NULL == root)
	{
		return 1;
	}

	return ((1 == InOrderTraverse(root->left, act_func, param)) &&
	(1 == act_func(root->data, param)) &&
	(1 == InOrderTraverse(root->right, act_func, param)));
}

static int PreOrderTraverse(node_t *root, action_func_t act_func, const void *param)
{
	if (NULL == root)
	{
		return 1;
	}

	return (1 == act_func(root->data, param)) 
	&& ((1 == PreOrderTraverse(root->left, act_func, param)) 
	&& (1 == PreOrderTraverse(root->right, act_func, param)));
}

static int PostOrderTraverse(node_t *root, action_func_t act_func, const void *param)
{
	if (NULL == root)
	{
		return 1;
	}

	return ((1 == PostOrderTraverse(root->left, act_func, param)) &&
	(1 == PostOrderTraverse(root->right, act_func, param)))
	&& (1 == act_func(root->data, param));
}

int AvlForEach(avl_t *avl, action_func_t action_func, const void *param, traversal_t order)
{
	if (order == IN_ORDER)
	{
		return InOrderTraverse(avl->root, action_func, param);
	}

	else if (order == PRE_ORDER)
	{
		return PreOrderTraverse(avl->root, action_func, param);
	}

	else
	{
		return PostOrderTraverse(avl->root, action_func, param);
	}
		
}


