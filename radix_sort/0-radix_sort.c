#include "sort.h"
#include <stdlib.h>

/**
 * get_max - Get the maximum value in an array
 * @array: Array to find maximum value in
 * @size: Size of the array
 *
 * Return: Maximum value in the array
 */
int get_max(int *array, size_t size)
{
    int max = array[0];
    size_t i;

    for (i = 1; i < size; i++)
    {
        if (array[i] > max)
            max = array[i];
    }
    return (max);
}

/**
 * counting_sort_radix - Sort an array of integers based on a specific digit
 * @array: Array to sort
 * @size: Size of the array
 * @exp: Current digit position (1, 10, 100, etc.)
 */
void counting_sort_radix(int *array, size_t size, int exp)
{
    int *output;
    int count[10] = {0};
    size_t i;

    output = malloc(sizeof(int) * size);
    if (!output)
        return;

        for (i = 0; i < size; i++)
        count[(array[i] / exp) % 10]++;

        for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

        for (i = size - 1; i < size; i--)
    {
        output[count[(array[i] / exp) % 10] - 1] = array[i];
        count[(array[i] / exp) % 10]--;
    }

    for (i = 0; i < size; i++)
        array[i] = output[i];

    free(output);
}

/**
 * radix_sort - Sort an array of integers in ascending order using Radix sort
 * @array: Array to sort
 * @size: Size of the array
 */
void radix_sort(int *array, size_t size)
{
    int max, exp;

    if (!array || size < 2)
        return;

    max = get_max(array, size);

    for (exp = 1; max / exp > 0; exp *= 10)
    {
        counting_sort_radix(array, size, exp);
        print_array(array, size);
    }
}