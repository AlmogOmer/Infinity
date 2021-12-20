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

static size_t Height(node_t *node);
static int GetBF(node_t *root);
static node_t *RotRight(node_t *root);
static node_t *RotLeft(node_t *root);
static node_t *Balance(node_t *root);
static node_t *CreateNode(const void *data);
static void DestroyRec(node_t *root);
static size_t AvlSizeRec(node_t *root);
static node_t *InsertRec(node_t *root, node_t *new_node, compare_func_t cmp_func, const void *param);
static node_t *FindMin(node_t *root);
static node_t *ConnectRight (node_t *root);
static node_t *RemoveRec(node_t *root, const void *data, compare_func_t cmp_func, const void *param);
static const void *FindRec(node_t *root, const void *data_to_match, compare_func_t cmp_func, const void *param);
static int InOrderTraverse(node_t *root, action_func_t act_func, const void *param);
static int PreOrderTraverse(node_t *root, action_func_t act_func, const void *param);
static int PostOrderTraverse(node_t *root, action_func_t act_func, const void *param);


static size_t Height(node_t *node)
{
	if (node)
	{
		return node->height;
	}
	
	return 0;
}

/* calculate the balance factor */
static int GetBF(node_t *root)
{
	return (Height(root->left) - Height(root->right));
}

static node_t *RotRight(node_t *root)
{
	node_t *pivot = root->left;
	root->left = pivot->right;
	pivot->right = root;

	root->height = 1 + (MAX(Height(root->left), Height(root->right)));
	pivot->height = 1 + (MAX(Height(pivot->left), Height(pivot->right)));

	return pivot;
}

static node_t *RotLeft(node_t *root)
{
	node_t *pivot = root->right;
	root->right = pivot->left;
	pivot->left = root;

	root->height = 1 + (MAX(Height(root->left), Height(root->right)));
	pivot->height = 1 + (MAX(Height(pivot->left), Height(pivot->right)));
	
	return pivot;

}

/* complexity O(1) */
static node_t *Balance(node_t *root)
{
	int balance_factor = 0;
	root->height = 1 + (MAX(Height(root->left), Height(root->right)));
	balance_factor = GetBF(root);
	if (2 == balance_factor)
	{	/* node in left subtree provoke balance */
		if (-1 == GetBF(root->left))
		{	/* first rotate left then right */
			root->left = RotLeft(root->left);
		}

		return RotRight(root);
	}
	if (-2 == balance_factor)
	{	/* node in right subtree provoke balance */
		if (1 == GetBF(root->right))
		{	/* first rotate right then left */
			root->right = RotRight(root->right);
		}
		
		return RotLeft(root);
	}
	
	
	return root;
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

	return Balance(root); 
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

static node_t *ConnectRight (node_t *root)
{
	if (NULL == root->left)
	{
		return root->right;
	}

	root->left = ConnectRight(root->left); /*connecting the right childe of the successor 
	                                       to be the left child of the node we sent to the function*/
	return root;
}

/* recursive function that find a node and remove it */
static node_t *RemoveRec(node_t *root, const void *data, compare_func_t cmp_func, const void *param)
{
	int cmp_result = 0;
	node_t *chlid_left;
	node_t *chlid_right;
	node_t *next = NULL;

	if (NULL == root)
	{
		return NULL;
	}

	cmp_result = cmp_func(root->data, data, param);

	if (cmp_result < 0)
	{
		root->right = RemoveRec(root->right, data, cmp_func, param);
		return Balance(root); 
	}
	if (cmp_result > 0)
	{
		root->left = RemoveRec(root->left, data, cmp_func, param);
		return Balance(root);
	}


	chlid_left = root->left;
	chlid_right = root->right;
	free(root);

	if (NULL == chlid_right)
	{
		return chlid_left;
	}

	next = FindMin(chlid_right);
	next->right = ConnectRight(chlid_right); 
	next->left = chlid_left;

	return Balance(next);
	

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
	switch (order)
	{
	case (IN_ORDER):
		return InOrderTraverse(avl->root, action_func, param);
		break;
	
	case (PRE_ORDER):
		return PreOrderTraverse(avl->root, action_func, param);
		break;

	case (POST_ORDER):
		return PostOrderTraverse(avl->root, action_func, param);
		break;
	}

}


