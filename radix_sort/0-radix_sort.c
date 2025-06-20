#include "sort.h"
#include <stdlib.h>

/**
 * get_max - Determines the highest number within an array
 * @array: The array to scan
 * @size: Total elements in the array
 *
 * Return: The largest integer found in the array
 */
static int get_max(int *array, size_t size)
{
	int max;
	size_t i;

	if (!array || size == 0)
		return (0);

	max = array[0];
	for (i = 1; i < size; i++)
	{
		if (array[i] > max)
			max = array[i];
	}
	return (max);
}

/**
 * counting_sort_radix - Executes a digit-based counting sort
 * @array: Array of integers to process
 * @size: Count of items in the array
 * @exp: The power of 10 that identifies the current digit
 */
static void counting_sort_radix(int *array, size_t size, int exp)
{
	int *output, *count;
	size_t i;
	int j;

	output = malloc(sizeof(int) * size);
	count = malloc(sizeof(int) * 10);
	if (!output || !count)
	{
		free(output);
		free(count);
		return;
	}
	/* Zero out all elements in the count array */
	for (j = 0; j < 10; j++)
		count[j] = 0;

	/* Tally up the occurrences of each digit at the current place */
	for (i = 0; i < size; i++)
		count[(array[i] / exp) % 10]++;

	/*
	 * Modify count so that it reflects positions
	 * in the final output
	 */
	for (j = 1; j < 10; j++)
		count[j] += count[j - 1];

	/* Construct the result array by placing elements in sorted order */
	for (i = size - 1; (int)i >= 0; i--)
	{
		output[count[(array[i] / exp) % 10] - 1] = array[i];
		count[(array[i] / exp) % 10]--;
	}

	/*
	 * Replace original array contents with sorted data
	 * based on the current digit
	 */
	for (i = 0; i < size; i++)
		array[i] = output[i];

	free(output);
	free(count);
}

/**
 * radix_sort - Implements LSD Radix Sort to sort an array in ascending order
 * @array: The array that needs sorting
 * @size: Total number of entries in the array
 */
void radix_sort(int *array, size_t size)
{
	int max, exp;

	if (!array || size < 2)
		return;

	max = get_max(array, size);

	/*
	 * Repeatedly apply counting sort for each digit level.
	 * 'exp' indicates which digit to target (1, 10, 100, etc.)
	 */
	for (exp = 1; max / exp > 0; exp *= 10)
	{
		counting_sort_radix(array, size, exp);
		print_array(array, size);
	}
}
