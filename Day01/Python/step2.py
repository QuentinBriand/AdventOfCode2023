#!/usr/bin/env python3

from parsers import intParser, charParser, parseLine

EXAMPLE_FILENAME = "resources/Day01/example"
EXAMPLE2_FILENAME = "resources/Day01/example2"
FIRST_FILENAME = "resources/Day01/longInput"

if __name__ == "__main__":
    with open(FIRST_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    parsers = [intParser, charParser]
    calibrations = []

    for line in lines:
        calibrations.append(parseLine(line, parsers))
    print("The answer is: {}".format(sum(calibrations)))
