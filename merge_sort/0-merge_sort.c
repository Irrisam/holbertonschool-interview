#include <stdio.h>
#include <stdlib.h>

/**
 * merge - Merges two subarrays into one sorted array
 * @array: Original array containing subarrays to merge
 * @temp: Temporary array to store the merged result
 * @left: Start index of left subarray
 * @mid: End index of left subarray
 * @right: End index of right subarray
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;    /* Index for left subarray */
    size_t j = mid + 1; /* Index for right subarray */
    size_t k = left;    /* Index for merged array */

    printf("Merging...\n");
    printf("[left]: ");
    for (size_t l = left; l <= mid; l++)
    {
        printf("%d", array[l]);
        if (l < mid)
            printf(", ");
    }
    printf("\n[right]: ");
    for (size_t l = mid + 1; l <= right; l++)
    {
        printf("%d", array[l]);
        if (l < right)
            printf(", ");
    }
    printf("\n");

    /* Merge the two subarrays */
    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
            temp[k++] = array[i++];
        else
            temp[k++] = array[j++];
    }

    /* Copy remaining elements from left subarray */
    while (i <= mid)
        temp[k++] = array[i++];

    /* Copy remaining elements from right subarray */
    while (j <= right)
        temp[k++] = array[j++];

    /* Copy merged elements back to original array */
    for (i = left; i <= right; i++)
        array[i] = temp[i];

    printf("[Done]: ");
    for (i = left; i <= right; i++)
    {
        printf("%d", array[i]);
        if (i < right)
            printf(", ");
    }
    printf("\n");
}

/**
 * merge_sort_recursive - Recursively divides and sorts array using merge sort
 * @array: Array to be sorted
 * @temp: Temporary array for merging
 * @left: Start index of the array
 * @right: End index of the array
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
    if (left < right)
    {
        /* Find middle point */
        size_t mid = left + (right - left) / 2;

        /* Sort first and second halves */
        if (left < mid)
            merge_sort_recursive(array, temp, left, mid);

        merge_sort_recursive(array, temp, mid + 1, right);

        /* Merge the sorted halves */
        merge(array, temp, left, mid, right);
    }
}

/**
 * merge_sort - Sorts an array of integers in ascending order using Merge Sort
 * @array: Array to be sorted
 * @size: Size of the array
 */
void merge_sort(int *array, size_t size)
{
    int *temp;

    if (!array || size < 2)
        return;

    /* Allocate memory for temporary array - using only one malloc call */
    temp = malloc(sizeof(int) * size);
    if (!temp)
        return;

    /* Call recursive merge sort function */
    merge_sort_recursive(array, temp, 0, size - 1);

    /* Free allocated memory */
    free(temp);
}