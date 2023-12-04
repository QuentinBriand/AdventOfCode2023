#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## main
##

EXAMPLE_FILENAME = "resources/Day04/example"
FIRST_FILENAME = "resources/Day04/longInput"

class Game():
    def __init__(self, desc) -> None:
        split = desc.split(':')
        self.id = int(split[0].split(' ')[-1])
        split = split[1].split('|')
        self.winning_numbers = [int(i) for i in split[0].split(' ') if len(i) != 0]
        self.my_numbers = [int(i) for i in split[1].split(' ') if len(i) != 0]

    def getValue(self) -> int:
        summedUpValues = 0
        nbrOfMatch = 0
        for nbr in self.my_numbers:
            if nbr in self.winning_numbers:
                nbrOfMatch += 1
                if summedUpValues == 0:
                    summedUpValues = 1
                else:
                    summedUpValues *= 2
        return nbrOfMatch, summedUpValues

    def __str__(self) -> str:
        return f"Game {self.id}"

    def __repr__(self) -> str:
        return str(self)


if __name__ == "__main__":
    with open(FIRST_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    totalValue = 0
    games = []
    for line in lines:
        g = Game(line)
        _, value = g.getValue()
        totalValue += value
        games.append(g)
    print(f"total value: {totalValue}")

    winning_score = {}
    numberOfScrathWon = 0
    length = len(games)
    for invertedIdx, g in enumerate(games[::-1]):
        value = 1
        infos = g.getValue()
        idx = length - invertedIdx
        for otherG in games[idx:idx + infos[0]]:
            value += winning_score[otherG.id]
        winning_score[g.id] = value
        numberOfScrathWon += value

    print("Number of scratch won:", numberOfScrathWon)
