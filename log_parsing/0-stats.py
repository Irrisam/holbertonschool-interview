#!/usr/bin/python3

import sys
import re
import signal


def print_statistics(total_file_size, status_codes):
    """ prints out the stats out the stdout"""
    print("File size: {}".format(total_file_size))

    valid_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    for code in valid_codes:
        if code in status_codes and status_codes[code] > 0:
            print("{}: {}".format(code, status_codes[code]))


def signal_handler(signum, frame):
    '''executes formula'''
    print_statistics(total_file_size, status_codes)
    sys.exit(0)


def parse_log_line(line):
    '''regex function scoring'''
    pattern = r'^(\S+) - \[([^\]]+)\] "GET /projects/260 HTTP/1\.1" (\d+) (\d+)$'

    match = re.match(pattern, line.strip())
    if match:
        try:
            status_code = int(match.group(3))
            file_size = int(match.group(4))
            return status_code, file_size
        except ValueError:
            return None, None

    return None, None


total_file_size = 0
status_codes = {}


if __name__ == "__main__":
    line_count = 0

    valid_status_codes = [200, 301, 400, 401, 403, 404, 405, 500]
    for code in valid_status_codes:
        status_codes[code] = 0

    signal.signal(signal.SIGINT, signal_handler)

    try:
        for line in sys.stdin:
            status_code, file_size = parse_log_line(line)

            if status_code is not None and file_size is not None:
                line_count += 1

                total_file_size += file_size

                if status_code in status_codes:
                    status_codes[status_code] += 1

                if line_count % 10 == 0:
                    print_statistics(total_file_size, status_codes)

        if line_count % 10 != 0 or line_count == 0:
            print_statistics(total_file_size, status_codes)

    except KeyboardInterrupt:
        pass
