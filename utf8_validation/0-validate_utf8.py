#!/usr/bin/python3
"""
    Determines if a given data set represents a valid UTF-8 encoding.
    """


def validUTF8(data):
    """
    Determines if a given data set represents a valid UTF-8 encoding.

    Args:
        data: List of integers representing bytes

    Returns:
        True if data is valid UTF-8 encoding, False otherwise
    """
    num_bytes_to_process = 0

    for byte in data:
        byte = byte & 0xFF

        if num_bytes_to_process == 0:
            if byte >> 7 == 0:
                continue
            elif byte >> 5 == 0b110:
                num_bytes_to_process = 1
            elif byte >> 4 == 0b1110:
                num_bytes_to_process = 2
            elif byte >> 3 == 0b11110:
                num_bytes_to_process = 3
            else:
                return False
        else:
            if byte >> 6 != 0b10:
                return False
            num_bytes_to_process -= 1

    return num_bytes_to_process == 0
