#!/usr/bin/env python3

from game import Game

EXAMPLE_FILENAME = "resources/Day02/example"
LONG_FILENAME = "resources/Day02/longInput"

maxs = {
    "red": 12,
    "green": 13,
    "blue": 14,
}

if __name__ == "__main__":
    with open(LONG_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    summedIds = 0

    for line in lines:
        g = Game(line)
        validGame = True
        for color in g.getAllColors():
            for c, nbr in color.items():
                if nbr > maxs[c]:
                    validGame = False
                    break

        if validGame:
            summedIds += g.id
    print(f"Summed up Id's: {summedIds}")
