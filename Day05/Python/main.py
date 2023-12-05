##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## main
##

import sys

EXAMPLE_FILENAME = "resources/Day05/example"
FIRST_FILENAME = "resources/Day05/longInput"

def parse():
    seeds = [int(i) for i in lines[0][7:].split(' ')]

    ranges = []
    lineCount = len(lines)
    lineIdx = 1
    for _ in range(1, lineCount):
        if (len(lines[lineIdx]) == 0):
            lineIdx += 1
            continue

        name = lines[lineIdx][:-1]
        lineIdx += 1
        currentContent = []
        while len(lines[lineIdx]) != 0:
            currentContent.append(lines[lineIdx])
            lineIdx += 1
            if lineIdx >= lineCount:
                break
        r = CustomRange(name, currentContent)
        ranges.append(r)

        if lineIdx >= lineCount:
            break
    return seeds, ranges

class CustomRange():
    def __init__(self, name, content) -> None:
        self.ranges = [[int(i) for i in s.split(' ')] for s in content]
        self.name = name.split(' ')[0]

    def evaluate(self, value):
        for dest, source, dist in self.ranges:
            if source <= value < source + dist:
                return value - source + dest
        return value

    def __repr__(self) -> str:
        return f"<CustomRange {self.name}: {self.ranges}>"

def feedThroughRanges(seedLowerBound, seedUpperBound, ranges):
    res = []
    for destination, source, length in ranges.ranges:
        if source < seedUpperBound and seedLowerBound < source + length:
            ra = max(source, seedLowerBound)
            rb = min(source + length, seedUpperBound)

            res.append((ra - source + destination, rb - source + destination))

            if seedLowerBound < source:
             res.extend(feedThroughRanges(seedLowerBound, source, ranges))

            if seedUpperBound > source + length:
                res.extend(feedThroughRanges(source + length, seedUpperBound, ranges))

            return res
    res.append((seedLowerBound, seedUpperBound))
    return res

def updateSeeds(seeds):
    new = []
    for seed in seeds:
        new.extend(feedThroughRanges(*seed, maps))

    return new

if __name__ == '__main__':
    with open(FIRST_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    seeds, ranges = parse()

    minDist = 100000000
    dsts = []
    for seed in seeds:
        dist = seed
        for r in ranges:
            dist = r.evaluate(dist)
        dsts.append(dist)

    print(f"Part 1: {min(dsts)}")

    seeds = [(seeds[i], seeds[i] + seeds[i + 1]) for i in range(0, len(seeds), 2)]
    for maps in ranges:
        seeds = updateSeeds(seeds)
    minDist = 100000000000
    for seed in seeds:
        minDist = min(minDist, seed[0])

    print(f"Part 2: {minDist}")
