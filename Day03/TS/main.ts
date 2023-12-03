import * as fs from "fs";

const directions = [
    [-1, -1],
    [-1, 0],
    [-1, 1],
    [0, -1],
    /*[0, 0],*/ [0, 1],
    [1, -1],
    [1, 0],
    [1, 1],
];

const symbols = ["*", "+", "-", "|", "\\", "/", "$", "#", "=", "%", "&", "@"];

function isSymbol(char: string): boolean {
    return char !== "." && symbols.includes(char);
}

function isValidIndex(row: number, col: number, numRows: number, numCols: number): boolean {
    return row >= 0 && col >= 0 && row < numRows && col < numCols;
}

function findFirstNonNumber(line: string, offset: number): number {
    for (let i = offset; i < line.length; i++) {
        if (isNaN(parseInt(line[i]))) {
            return i - 1;
        }
    }

    return line.length - 1;
}

function sumPartNumbers(engine: string[]) {
    const numRows = engine.length;
    const numCols = engine[0].length;
    const gears = {} as { [key: number]: number[] };
    let sum = 0;

    for (let i = 0; i < numRows; i++) {
        for (let j = 0; j < numCols; j++) {
            if (!isNaN(parseInt(engine[i][j]))) {
                let isPartNumber = false, isGear = false;
                let currentNumberBounds = [j, findFirstNonNumber(engine[i], j)];
                let gearId = -1;
                for (let x = j; x <= currentNumberBounds[1]; x++) {
                    for (const [dx, dy] of directions) {
                        const newRow = i + dx;
                        const newCol = x + dy;
                        if (newRow < 0 || newCol < 0 || newRow >= numRows || newCol >= numCols) {
                            continue;
                        }
                        if (isSymbol(engine[newRow][newCol])) {
                            isPartNumber = true;
                        }
                        if (engine[newRow][newCol] === "*") {
                            isGear = true;
                            gearId = newRow * numCols + newCol;
                        }
                        if (isGear || isPartNumber) {
                            break;
                        }
                    }
                }
                const nb = Number(
                    engine[i].substring(currentNumberBounds[0], currentNumberBounds[1] + 1)
                );
                if (isPartNumber) {
                    sum += nb;
                }

                if (isGear) {
                    if (gears[gearId] === undefined) {
                        gears[gearId] = [nb, 1];
                    } else {
                        gears[gearId][0] *= nb;
                        gears[gearId][1]++;
                    }
                }
                j += currentNumberBounds[1] - currentNumberBounds[0];
            }
        }
    }
    return {
        part1: sum,
        part2: Object.values(gears).reduce((acc, [nb, count]) => {
            if (count !== 1) {
                return acc + nb;
            }
            return acc;
        }, 0),
    };
}

const main = async () => {
    const data = fs.readFileSync("../../resources/Day03/antoine", "utf8");

    const lines = data.split("\n");

    const result = sumPartNumbers(lines);
    console.log("Part 1", result.part1);
    console.log("Part 2", result.part2);
};

main();
