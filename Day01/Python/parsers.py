##
## EPITECH PROJECT, 2023
## AdventOfCode2023
## File description:
## parsers
##

def intParser(line, idx):
    char = line[idx]
    if hasattr(char, 'isdigit') and char.isdigit():
        return int(char)
    return -1

def charParser(line, idx):
    availables = {
        'one': (3, 1),
        'two': (3, 2),
        'three': (5, 3),
        'four': (4, 4),
        'five': (4, 5),
        'six': (3, 6),
        'seven': (5, 7),
        'eight': (5, 8),
        'nine': (4, 9),
    }
    for key, value in availables.items():
        if line[idx:idx + value[0]] == key:
            return value[1]
    return -1

def parseLine(line, parsers):
    firstDigit = -1
    secondDigit = -1
    lineLength = len(line)

    for idx in range(lineLength):
        if firstDigit == -1:
            for parser in parsers:
                firstDigit = parser(line, idx)
                if firstDigit != -1:
                    break
        if secondDigit == -1:
            for parser in parsers:
                secondDigit = parser(line, lineLength - idx - 1)
                if secondDigit != -1:
                    break
        if firstDigit != -1 and secondDigit != -1:
            break
    if firstDigit == -1 and secondDigit == -1:
        return 0
    return (secondDigit + firstDigit * 10)
