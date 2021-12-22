#include<stdio.h>
#include<string.h>
#include "hash_table.h"
#include "doubly_linked_list.h"

#define UNUSED(x) (void)(x)

/*typedef int (*cmp_func_t)(const void *curr_data, const void *requested_data, const void *param);
typedef size_t (*hash_func_t)(const void *new_elem, const void *param);
typedef int (*action_func_t)(const void *data, const void *param);*/ /* SUCCESS = 0, FAIL = 1*/

void Test();
size_t StringHash(const void *data, const void *param);
static int Strcmp(const void *data1, const void *data2, const void *param);

int main()
{
    Test();
	return 0;
}

void Test()
{
    hash_t *hash = NULL;
    hash = HashCreate(StringHash, Strcmp, 100, NULL);





    HashDestroy(hash);
}



size_t StringHash(const void *data, const void *param)
{
    char *str = (char *) data;
    size_t hash = 0;
    UNUSED(param);

    while (*str)
    {
        hash += *str;
        ++str;
    }

    return hash;
}


static int Strcmp(const void *data1, const void *data2, const void *param)
{
    UNUSED(param);
    return (0 == strcmp(data1, data2));
}


