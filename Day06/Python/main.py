##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## main
##

from math import ceil, floor

EXAMPLE_FILENAME = "resources/Day06/example"
FIRST_FILENAME = "resources/Day06/longInput"

class Polynomial():
    def __init__(self, a, b, c) -> None:
        self.a = a
        self.b = b
        self.c = c

    def getDiscriminant(self):
        return self.b ** 2 - 4 * self.a * self.c

    def getRoots(self):
        d = self.getDiscriminant()
        if d < 0:
            print("This is becoming to much complicated. ABORT THE MISSION !")
        elif d == 0:
            return [-self.b / (2 * self.a)]
        else:
            return [(-self.b + d ** 0.5) / (2 * self.a), (-self.b - d ** 0.5) / (2 * self.a)]

    def getAnswersCount(self):
        if self.getDiscriminant() == 1:
            print("You are lucky, there is only one solution !")
            return 1
        roots = self.getRoots()
        smoothenedRoots = [roots[0] + 1 if roots[0].is_integer() else roots[0], roots[1] -1 if roots[1].is_integer() else roots[1]]
        smoothenedRoots = [ceil(smoothenedRoots[0]), floor(smoothenedRoots[1])]
        return smoothenedRoots[1] - smoothenedRoots[0] + 1

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        return f"{self.a}x² + {self.b}x {'+' if self.c > 0 else '-'} {abs(self.c)}"

if __name__ == '__main__':
    with open(FIRST_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    times = [int(x) for x in lines[0].split(' ')[1:] if len(x) != 0]
    record = [int(x) for x in lines[1].split(' ')[1:] if len(x) != 0]

    chances = 1
    for i in range(len(times)):
        poly = Polynomial(-1, times[i], -record[i])
        chances *= poly.getAnswersCount()

    print("Part 1:", chances)
    concatTimes = int(''.join([str(x) for x in times]))
    concatRecord = int(''.join([str(x) for x in record]))

    poly = Polynomial(-1, concatTimes, -concatRecord)
    print("Part 2:", poly.getAnswersCount())
