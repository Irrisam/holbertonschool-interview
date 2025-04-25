#include "sandpiles.h"
#include <stdbool.h>

/**
 * is_stable - check if the sandpile is stable
 */
int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				return (false);
			}
		}
	}
	return (true);
}

/**
 * topple - topple the sandpile at the given coordinates
 */
void topple(int grid[3][3], int grid_tmp[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				grid[i][j] -= 4;
				if (i > 0)
					grid_tmp[i - 1][j]++;
				if (i < 2)
					grid_tmp[i + 1][j]++;
				if (j > 0)
					grid_tmp[i][j - 1]++;
				if (j < 2)
					grid_tmp[i][j + 1]++;
			}
		}
	}
	sandpiles_sum(grid, grid_tmp);
}

/**
 * sandpiles_sum- sandpile addition
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;
	int grid_tmp[3][3];
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			grid1[i][j] += grid2[i][j];
			grid_tmp[i][j] = 0;
		}
	}

	while (!is_stable(grid1))
	{
		printf("=\n");
		print_grid(grid1);
		topple(grid1, grid_tmp);
	}
}

/**
 * print_grid- print grid
 * Return: printed grid
 */
static void print_grid(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}
