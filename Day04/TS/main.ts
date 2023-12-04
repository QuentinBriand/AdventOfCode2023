import * as fs from "fs";
const wonCards: { [key: number]: number } = {};

const parseCard = (line: string, idx: number) => {
    if (wonCards[idx] === undefined) {
        wonCards[idx] = 1;
    }
    const [name, cards] = line.split(":");
    const [winning, numbers] = cards.split("|").map(card =>
        card
            .split(" ")
            .map(n => n.trim())
            .filter(n => n.length > 0)
    );
    let res = 0,
        nbWon = idx;
    for (const number of numbers) {
        if (winning.includes(number)) {
            res = res === 0 ? 1 : res * 2;
            nbWon++;
            if (wonCards[nbWon] === undefined) {
                wonCards[nbWon] = 1;
            }
            wonCards[nbWon] += wonCards[idx]
        }
    }
    return { part1: res, part2: 0 };
};

const main = async () => {
    const data = fs.readFileSync("../../resources/Day04/antoine", "utf8");

    const lines = data.split("\n");
    let res1 = 0,
        res2 = 0;

    let idx = 1;
    for (const line of lines) {
        if (line.length > 0) {
            const result = parseCard(line, idx);
            res1 += result.part1;
            res2 += result.part2;
            idx++;
        }
    }
    console.log(wonCards);
    console.log("Part 1:", res1);
    console.log(
        "Part 2:",
        Object.values(wonCards).reduce((a, b) => a + b, 0)
    );
};

main();
