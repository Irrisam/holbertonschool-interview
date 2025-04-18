#ifndef _SORT_H_
#define _SORT_H_

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_array(const int *array, size_t size);
void merge_sort(int *array, size_t size);
void merge_sort_recursive(int *array, size_t start, size_t end, int *temp);
void merge(int *array, size_t start, size_t middle, size_t end, int *temp);
void merge_sort(int *array, size_t size);


#endif /* _SORT_H_ */
