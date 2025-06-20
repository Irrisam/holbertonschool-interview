#!/usr/bin/python3
"""Prime Game logic and winner evaluation."""


def isWinner(x, nums):
    """
    Determine which player secures the most wins in a series of rounds

    Args:
    x: total number of rounds to play
    nums: list of integers representing the limit for each round

    Returns:
    The name of the overall winner, or None if both win equally
    """
    if not nums or x != len(nums):
        return None

    max_n = max(nums)
    if max_n < 2:
        return "Ben"

    is_prime = [True] * (max_n + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, int(max_n ** 0.5) + 1):
        if is_prime[i]:
            for j in range(i * i, max_n + 1, i):
                is_prime[j] = False

    maria_wins = 0
    ben_wins = 0

    for n in nums:
        if n < 2:
            ben_wins += 1
            continue

        available = [True] * (n + 1)
        moves = 0

        while True:
            found = False
            for i in range(2, n + 1):
                if available[i] and is_prime[i]:
                    for j in range(i, n + 1, i):
                        available[j] = False
                    moves += 1
                    found = True
                    break

            if not found:
                break

        if moves % 2 == 1:
            maria_wins += 1
        else:
            ben_wins += 1

    if maria_wins > ben_wins:
        return "Maria"
    elif ben_wins > maria_wins:
        return "Ben"
    else:
        return None
