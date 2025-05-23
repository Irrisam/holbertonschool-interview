#!/usr/bin/python3
"""    Calculate how many square units of water will be retained
after it rains.

    """


def rain(walls):
    """
    Calculate how many square units of water will be retained after it rains.
    """
    if not walls:
        return 0

    n = len(walls)
    total_water = 0

    left_max = [0] * n
    right_max = [0] * n

    left_max[0] = walls[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i-1], walls[i])

    right_max[n-1] = walls[n-1]
    for i in range(n-2, -1, -1):
        right_max[i] = max(right_max[i+1], walls[i])

    for i in range(n):
        water_level = min(left_max[i], right_max[i])
        total_water += water_level - walls[i]

    return total_water
