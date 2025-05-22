#!/usr/bin/python3
"""Module for calculating island perimeter."""


def island_perimeter(grid):
    """
    Calculate the perimeter of an island in a grid.

    Args:
        grid (list): A list of lists of integers where:
                    - 0 represents water
                    - 1 represents land
                    - Each cell is a square with side length 1
                    - Cells are connected horizontally/vertically only

    Returns:
        int: The perimeter of the island

    Note:
        - Grid is completely surrounded by water
        - There is only one island (or nothing)
        - No lakes inside the island
        - Grid dimensions don't exceed 100x100
    """
    if not grid or not grid[0]:
        return 0

    rows = len(grid)
    cols = len(grid[0])
    perimeter = 0

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 1:  # Found land
                # Check all 4 directions
                # Each side starts as part of perimeter
                sides = 4

                # Check up
                if i > 0 and grid[i-1][j] == 1:
                    sides -= 1

                # Check down
                if i < rows - 1 and grid[i+1][j] == 1:
                    sides -= 1

                # Check left
                if j > 0 and grid[i][j-1] == 1:
                    sides -= 1

                # Check right
                if j < cols - 1 and grid[i][j+1] == 1:
                    sides -= 1

                perimeter += sides

    return perimeter
