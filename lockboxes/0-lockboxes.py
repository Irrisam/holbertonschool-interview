def canUnlockAll(boxes):
    """Determines if all boxes can be opened starting from box 0.
    Args:
        boxes: List of lists where boxes[i] contains keys found in box i
    Returns:
        bool: True if all boxes can be opened, False otherwise
    """
    if not boxes:
        return True
    n = len(boxes)
    opened = set([0])  # Box 0 is initially unlocked
    keys = set(boxes[0])  # Keys from box 0
    # Keep trying to open new boxes until no more can be opened
    while True:
        new_boxes_opened = False
        # Try to open boxes with available keys
        for key in list(keys):
            if key < n and key not in opened:
                opened.add(key)
                keys.update(boxes[key])  # Add keys from newly opened box
                new_boxes_opened = True
        # If no new boxes were opened in this iteration, we're done
        if not new_boxes_opened:
            break
    return len(opened) == n
# Alternative BFS solution
def canUnlockAll_bfs(boxes):
    """
    BFS approach to solve the same problem.
    """
    if not boxes:
        return True
    n = len(boxes)
    opened = [False] * n
    opened[0] = True
    queue = [0]  # Start with box 0
    while queue:
        current_box = queue.pop(0)
        # Get all keys from current box
        for key in boxes[current_box]:
            # If key corresponds to a valid, unopened box
            if key < n and not opened[key]:
                opened[key] = True
                queue.append(key)
    return all(opened)
# Test cases
def test_canUnlockAll():
    """Test the function with various cases"""
    # Test case 1: All boxes can be opened
    boxes1 = [[1], [2], [3], [4], []]
    print(f"Test 1: {boxes1}")
    print(f"Result: {canUnlockAll(boxes1)}")  # Should be True
    # Test case 2: Not all boxes can be opened
    boxes2 = [[1, 3], [3, 0, 1], [2], [0, 1, 3]]
    print(f"\nTest 2: {boxes2}")
    print(f"Result: {canUnlockAll(boxes2)}")  # Should be False
    # Test case 3: Single box
    boxes3 = [[]]
    print(f"\nTest 3: {boxes3}")
    print(f"Result: {canUnlockAll(boxes3)}")  # Should be True
    # Test case 4: Keys that don't correspond to boxes
    boxes4 = [[1, 4, 6], [2], [0, 4, 1], [5, 6, 2]]
    print(f"\nTest 4: {boxes4}")
    print(f"Result: {canUnlockAll(boxes4)}")  # Should be True
    # Test case 5: Unreachable box
    boxes5 = [[1], [0], [2]]
    print(f"\nTest 5: {boxes5}")
    print(f"Result: {canUnlockAll(boxes5)}")  # Should be False


if __name__ == "__main__":
    test_canUnlockAll()