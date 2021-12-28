#include <assert.h>
#include "comparison.h"

void *IterBinarySearch(void * base, size_t nmemb, size_t size, cmp_func_t cmp_func, const void *data)
{
    void *mid;
    int diff;

    while(1 <= nmemb)
    {
        mid = (char *) base + (nmemb / 2) * size;
	    diff = cmp_func(mid, data);

        if (0 == diff)
        {
            return mid;
        }

        if (diff > 0) /*mid is bigger*/
        {
            nmemb = nmemb / 2;
        }

        else
        {
            nmemb = nmemb - (nmemb / 2);
            base = mid;
        }
    }

    return NULL;
}


void *RecBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t cmp_func, const void *data)
{
	void *mid = (char *) base + (nmemb / 2) * size;
	int diff = cmp_func(mid, data);

	if (0 == diff)
	{
		return mid;
	}

	if (1 == nmemb)
	{
		return NULL;
	}

	if (diff > 0) /*mid is bigger*/
	{
		return RecBinarySearch(base, nmemb / 2, size, cmp_func, data);
	}

	return RecBinarySearch(mid, nmemb - (nmemb / 2), size, cmp_func, data);
}






