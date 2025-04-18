#!/usr/bin/python3
#include <stdio.h>
#include <stdlib.h>

/**
 * merge - Merges two subarrays into one sorted array
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid;
    size_t k = left;
    
    printf("Merging...\n");
    printf("[left]: ");
    for (size_t l = left; l < mid; l++)
    {
        printf("%d", array[l]);
        if (l < mid - 1)
            printf(", ");
    }
    printf("\n");

    printf("[right]: ");
    for (size_t l = mid; l < right; l++)
    {
        printf("%d", array[l]);
        if (l < right - 1)
            printf(", ");
    }
    printf("\n");
    
    while (i < mid && j < right)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }
    
    while (i < mid)
        temp[k++] = array[i++];
    
    while (j < right)
        temp[k++] = array[j++];
    
    for (i = left; i < right; i++)
        array[i] = temp[i];
    
    printf("[Done]: ");
    for (i = left; i < right; i++)
    {
        printf("%d", array[i]);
        if (i < right - 1)
            printf(", ");
    }
    printf("\n");
}

/**
 * merge_sort_recursive - Recursive implementation of the merge sort algorithm
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
    if (right - left > 1)
    {
        size_t mid = left + (right - left) / 2 + (right - left) % 2;
        merge_sort_recursive(array, temp, left, mid);
        merge_sort_recursive(array, temp, mid, right);
        merge(array, temp, left, mid, right);
    }
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge sort
 */
void merge_sort(int *array, size_t size)
{
    if (!array || size < 2)
        return;
    
    int *temp = malloc(sizeof(int) * size);
    if (!temp)
        return;
    
    merge_sort_recursive(array, temp, 0, size);
    
    free(temp);
}