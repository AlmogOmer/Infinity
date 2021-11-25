#include "variable_alloc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    void *pool = NULL;
    var_alloc_t *vsa = NULL;
    size_t pool_size = 200;

    pool = malloc(pool_size);
    if(NULL == pool)
    {
        exit(1);
    }

    vsa = VSAInit(pool,pool_size);
    
  

    free(pool);

    return 0;
}
