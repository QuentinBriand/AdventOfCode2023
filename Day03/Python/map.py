##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## Map
##

class Map():
    def __init__(self, map) -> None:
        for line in map:
            assert len(line) == len(map[0])
        self.empty_symbol = '.'
        self.part_symbols = ['*', '+', '-', '|', '\\', '/', '$', '#', '=', '%', '&', '@']
        self.map = map
        self.parts_found = 0
        self.offsets = [(0, 1), (0, -1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1)]
        self.parts = {}
        self.gears = []

    def scan(self):
        length = len(self.map[0])
        for y in range(length):
            for x in range(length):
                if self.map[y][x] in self.part_symbols:
                    parts_found = self.apply_on_neighbours(x, y, lambda x, y: self.find_part(x, y))
                    if len(parts_found) == 2 and self.map[y][x] == '*':
                        self.gears.append(self.parts[parts_found[0]] * self.parts[parts_found[1]])
        return (self.parts, self.gears)

    def find_part(self, x, y):
        if not self.map[y][x].isdigit():
            return
        self.explore_part(x, y, self.parts_found)
        self.parts_found += 1

        self.map[y] = self.map[y][:x] + self.empty_symbol + self.map[y][x + 1:]
        return self.parts_found - 1

    def explore_part(self, x, y, partId):
        if not self.map[y][x].isdigit():
            return

        firstX = x - 1
        while firstX >= 0 and self.map[y][firstX].isdigit():
            firstX -= 1

        lastX = x + 1
        while lastX < len(self.map[y]) and self.map[y][lastX].isdigit():
            lastX += 1

        self.parts[partId] = int(self.map[y][firstX + 1:lastX])
        self.map[y] = self.map[y][:firstX + 1] + self.empty_symbol * (lastX - firstX - 1) + self.map[y][lastX:]


    def apply_on_neighbours(self, x, y, func):
        reses = []
        for offset_x, offset_y in self.offsets:
            if x + offset_x < 0 or x + offset_x >= len(self.map[y]):
                continue
            if y + offset_y < 0 or y + offset_y >= len(self.map):
                continue
            res = func(x + offset_x, y + offset_y)
            if res is not None:
                reses.append(res)
        return reses

    def __repr__(self) -> str:
        return str(self)

    def __str__(self) -> str:
        return "\n".join(self.map)
