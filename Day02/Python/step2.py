#!/usr/bin/env python3

from game import Game

EXAMPLE_FILENAME = "resources/Day02/example2"
LONG_FILENAME = "resources/Day02/longInput"

if __name__ == "__main__":
    with open(LONG_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    summedUpProducts = 0
    for line in lines:
        g = Game(line)
        maxColors = {}
        for cSet in g.sets:
            for color, nbr in cSet.items():
                if color in maxColors:
                    maxColors[color] = max(maxColors[color], nbr)
                else:
                    maxColors[color] = nbr
        product = 1
        for color, nbr in maxColors.items():
            product *= nbr
        summedUpProducts += product
    print("The answer is: {}".format(summedUpProducts))
