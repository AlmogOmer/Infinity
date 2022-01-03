#ifndef __HEAP_H__
#define __HEAP_H__
#include <stddef.h>
#include"common_types.h"

/* typedef int (*cmp_func_t)(const void *new_elem, const void *curr_elem, const void *param); */ 
/* is in common_types  */

typedef struct Heap heap_t;

extern heap_t *HeapCreate(cmp_func_t compare, const void *param);

extern void HeapDestroy(heap_t *heap);

/* returns 0 if success, 1 if failed*/
extern int HeapPush(heap_t *heap, const void *data); 

extern void HeapPop(heap_t *heap);

extern void *HeapPeek(heap_t *heap);

/* 1 if empty, 0 if not*/
extern int HeapIsEmpty(const heap_t *heap);

extern size_t HeapSize(const heap_t *heap);

extern void *HeapRemove(heap_t *heap, const void *data, match_func_t is_match, void *param);

extern void *HeapFind(const heap_t *heap, const void *data, match_func_t is_match, void *param);

#endif
