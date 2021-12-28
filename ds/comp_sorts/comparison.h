#ifndef __COMPARISON_H__
#define __COMPARISON_H__

#include <stdlib.h>
typedef int (*cmp_func_t)(const void*, const void*);

void swap(int *x, int *y);
void bubble(int *arr, size_t size);
void insertion(int *arr, size_t size);
void selection(int *arr, size_t size);
void quick_sort(void *arr, size_t arr_size, size_t elem_size, cmp_func_t cmp_func);
void MergeSort(void *base, size_t nmemb, size_t size, cmp_func_t cmp_func);
void *IterBinarySearch(void * base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);
void *RecBinarySearch(void * base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);
#endif


