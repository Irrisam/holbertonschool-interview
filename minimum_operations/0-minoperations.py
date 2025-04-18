#!/usr/bin/python3
def minOperations(n):
    """
    Calculate the fewest number of operations needed to get n 'H' characters
    starting with just one 'H' character, using only Copy All and Paste operations.

    Args:
        n: The desired number of 'H' characters

    Returns:
        The minimum number of operations, or 0 if impossible
    """
    if n <= 1:
        return 0

    operations = 0
    d = 2

    while n > 1:
        while n % d == 0:
            operations += d
            n //= d
        d += 1
        if d * d > n and n > 1:
            operations += n
            break

    return operations
