#!/usr/bin/env python3

from map import Map

EXAMPLE_FILENAME = "resources/Day03/example"
LONG_FILENAME = "resources/Day03/longInput"

if __name__ == "__main__":
    with open(LONG_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    m = Map(lines)
    summedUpParts = 0
    parts, gears = m.scan()
    for partId, partNumber in parts.items():
        summedUpParts += partNumber

    print(f"Summed up: {summedUpParts}")
    print(f"Summed up gears: {sum(gears)}")
