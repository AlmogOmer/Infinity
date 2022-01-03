#ifndef __COMMON_TYPES__
#define __COMMON_TYPES__

typedef int (*cmp_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int (*action_func_t)(const void *data, const void *param); /* SUCCESS = 0, FAIL = 1*/
typedef int (*match_func_t)(const void *data1, const void *data2, const void *param);

#endif



