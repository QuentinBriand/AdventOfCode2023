##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## game
##


class Game():
    def __init__(self, string) -> None:
        splitted = string[5:].split(' ')
        self.id = int(splitted[0][:-1])
        allSetsStr = ''.join(splitted[1:])
        self.parse_sets(allSetsStr)

    def parse_sets(self, string):
        splitted = string.split(';')
        self.sets = []
        for cSet in splitted:
            self.sets.append(self.parse_set(cSet))

    def parse_set(self, string):
        splitted = string.split(',')
        colors = {}
        for info in splitted:
            idx = 0
            nbr = 0
            while info[idx].isdigit():
                nbr = nbr * 10 + int(info[idx])
                idx += 1
            colors[info[idx:]] = nbr
        return colors

    def getAllColors(self):
        allColors = []
        for cSet in self.sets:
            allColors.append({})
            for color, nbr in cSet.items():
                if color in allColors[-1]:
                    allColors[-1][color] += nbr
                else:
                    allColors[-1][color] = nbr
        return allColors

    def __repr__(self) -> str:
        return self.__str__()

    def __str__(self) -> str:
        st = f"Game {self.id}\n"
        for idx, cSet in enumerate(self.sets):
            st += f"  Set {idx + 1}\n"
            for idy, (color, nbr) in enumerate(cSet.items()):
                st += f"    {color}: {nbr}"
                if not (idy == len(cSet.items()) - 1 and idx == len(self.sets) - 1):
                    st += "\n"
        return st
