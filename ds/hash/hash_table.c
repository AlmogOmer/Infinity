#include "hash_table.h"
#include "doubly_linked_list.h"
#include <stdio.h>
#include<stdlib.h>
#include <assert.h>	

struct Hash
{
    hash_func_t hash_func;
	size_t hash_size;
	dlist_t **hash_table;
	cmp_func_t cmp_func;
	const void *param;
};

/* Create new hash table*/
hash_t *HashCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t hash_size, const void *param)
{
    hash_t *hash = (hash_t *) malloc(sizeof(hash_t));
	if (!hash)
	{
		return NULL;
	}

	hash->hash_func = hash_func;
	hash->hash_size = hash_size;
	hash->hash_table = (dlist_t **) calloc(hash_size, sizeof(dlist_t *));
	if (!hash->hash_table)
	{
		free(hash);
		return NULL;
	}

	hash->cmp_func = cmp_func;
	hash->param = param;

	return hash;
}

/* Destroy hash table*/
void HashDestroy(hash_t *hash)
{
    size_t i = 0;

	assert(hash);

	for (i = 0; i < hash->hash_size; i++)
	{
		if (hash->hash_table[i])
		{
			DListDestroy(hash->hash_table[i]);
		}
	}

	free(hash->hash_table);
	free(hash);
}

/* Insert a new data - 0 if succes, 1 fail */
int HashInsert(hash_t *hash, const void *data)
{
    size_t i = 0;

	assert(hash);
	assert (!HashFind(hash, data));

	i = (hash->hash_func(data, hash->param)) % hash->hash_size;

	if (!hash->hash_table[i])
	{
		hash->hash_table[i] = DListCreate();
		if (!hash->hash_table[i])
		{
			return 1;
		}
	}

	return DListIterIsEqual(DListPushBack(hash->hash_table[i], data), DListEnd(hash->hash_table[i]));
}

/* Remove a data from hash table */
void HashRemove(hash_t *hash, const void *data)
{
	size_t i = 0;
	dlist_iter_t iter;

	assert(hash);

	i = (hash->hash_func(data, hash->param)) % hash->hash_size;
	
	if (!hash->hash_table[i])
	{
		return;
	}

	iter = DListFind(DListBegin(hash->hash_table[i]), DListEnd(hash->hash_table[i]), hash->cmp_func, hash->param, data);

	if (DListIterIsEqual(iter, DListEnd(hash->hash_table[i])))
	{
		return;
	}

	DListRemove(iter);

}

/* Number of element in table in total */
size_t HashSize(hash_t *hash)
{
	size_t counter = 0;
	size_t i = 0;

	assert(hash);

	for (i = 0; i < hash->hash_size; ++i)
	{
		if (hash->hash_table[i])
		{
			counter += DListSize(hash->hash_table[i]);
		}
	}
	
	return counter;
}

/* If hash table is Empty return 1 */
int HashIsEmpty(hash_t *hash)
{
	size_t i = 0;

	assert(hash);

	for (i = 0; i < hash->hash_size; i++)
	{
		if (hash->hash_table[i] && 0 != DListSize(hash->hash_table[i]))
		{
			return 0;
		}
	}    
	
	return 1;
}


/* Find a data in the table  */
void *HashFind(hash_t *hash, const void *data)
{
	dlist_iter_t iter;
	size_t i = 0;
	assert(hash);

	i = (hash->hash_func(data, hash->param)) % hash->hash_size;
	if(hash->hash_table[i])
	{
		iter = DListFind(DListBegin(hash->hash_table[i]), DListEnd(hash->hash_table[i]), hash->cmp_func, hash->param, data);
		if (!DListIterIsEqual(iter, DListEnd(hash->hash_table[i])))
		{
			return DListIterGetData(iter);
		}	
		
	}

	return NULL;

}

/* Execute operation on each element in table */
int HashForEach(hash_t *hash, action_func_t action_func, const void *param)
{
	size_t i;
	for (i = 0; i < hash->hash_size; ++i)
	{
		if (hash->hash_table[i])
		{
			if (!DListForEach(DListBegin(hash->hash_table[i]), DListEnd(hash->hash_table[i]), action_func, param))
			{
				return 0;
			}
		}
	}

	return 1;

}



