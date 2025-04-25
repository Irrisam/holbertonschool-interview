#include <stdio.h>
#include <stdlib.h>

/**
 * print_array - Prints an array of integers
 * @array: The array to be printed
 * @size: Number of elements in @array
 */
void print_array(const int *array, size_t size)
{
    size_t i;

    for (i = 0; i < size; i++)
    {
        printf("%d", array[i]);
        if (i < size - 1)
            printf(", ");
    }
    printf("\n");
}

/**
 * merge - Merges two subarrays into one sorted array
 * @array: Original array containing subarrays to merge
 * @temp: Temporary array to store the merged result
 * @left: Start index of left subarray
 * @mid: End index of left subarray / start of right subarray - 1
 * @right: End index of right subarray
 */
void merge(int *array, int *temp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid + 1;
    size_t k = left;
    size_t l;

    printf("Merging...\n");
    printf("[left]: ");
    for (l = left; l <= mid; l++)
    {
        printf("%d", array[l]);
        if (l < mid)
            printf(", ");
    }
    printf("\n[right]: ");
    for (l = mid + 1; l <= right; l++)
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
 * merge_sort_recursive - Recursively sorts an array using merge sort algorithm
 * @array: Array to be sorted
 * @temp: Temporary array for merging
 * @left: Start index of the array
 * @right: End index of the array
 *
 * Description: Implements top-down merge sort where left subarray size <= right
 */
void merge_sort_recursive(int *array, int *temp, size_t left, size_t right)
{
    if (left < right)
    {
        size_t mid;
        
        /* Calculate mid ensuring left subarray is <= right subarray */
        if ((right - left) % 2 == 0)
            mid = left + (right - left) / 2 - 1;
        else
            mid = left + (right - left) / 2;

        /* Sort left subarray */
        merge_sort_recursive(array, temp, left, mid);
        
        /* Sort right subarray */
        merge_sort_recursive(array, temp, mid + 1, right);
        
        /* Merge the sorted subarrays */
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

    /* Print initial array */
    print_array(array, size);

    /* Allocate memory for temporary array */
    temp = malloc(sizeof(int) * size);
    if (!temp)
        return;

    /* Call recursive merge sort function */
    merge_sort_recursive(array, temp, 0, size - 1);

    /* Free memory */
    free(temp);
}