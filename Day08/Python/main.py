##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## main
##

from math import gcd

EXAMPLE_FILENAME = "resources/Day08/example"
EXAMPLE2_FILENAME = "resources/Day08/example2"
FIRST_FILENAME = "resources/Day08/longInput"

directionsEnum = {
    'L': 0,
    'R': 1,
}

def parcour(directions, startNodeNames):
    directionsLength = len(directions)
    cIdxs = [0 for _ in range(len(startNodeNames))]
    pathCount = 0
    while any([not i.endswith('Z') for i in startNodeNames]):
        pathCount += 1
        for idx, startNodeName in enumerate(startNodeNames):
            startNodeNames[idx] = nodes[startNodeName][directionsEnum[directions[cIdxs[idx] % directionsLength]]]
            cIdxs[idx] += 1
    return pathCount

if __name__ == '__main__':
    with open(EXAMPLE_FILENAME) as f:
        lines = [line.strip() for line in f.readlines()]

    directions = lines[0]

    nodes = {}

    for line in lines[2:]:
        splitted = line.split(' ')
        nodes[splitted[0]] = (splitted[2][1:-1], splitted[3][:-1])

    print(f"Took us {parcour(directions, ['AAA'])} steps to go to ZZZ from AAA")

    startNodeNames = [i[:3] for i in lines[2:] if i[:3].endswith('A')]

    for name in startNodeNames:
        pathCount = parcour(directions, [name])
        print(f"Took us {pathCount} steps to go to ZZZ")

    dsts = [parcour(directions, [name]) for name in startNodeNames]

    lcm = 1
    for dst in dsts:
        lcm = lcm * dst // gcd(lcm, dst)
    print(lcm)
