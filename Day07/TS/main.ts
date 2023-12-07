import * as fs from "fs";

const cards = {
    A: 14,
    K: 13,
    Q: 12,
    J: 0,
    T: 10,
    "9": 9,
    "8": 8,
    "7": 7,
    "6": 6,
    "5": 5,
    "4": 4,
    "3": 3,
    "2": 2,
};

const handValues = {
    "Five of a kind": 9,
    "Four of a Kind": 8,
    "Full House": 7,
    "Three of a Kind": 4,
    "Two Pair": 3,
    "One Pair": 2,
    "High Card": 1,
};

const getHandValue = (hand: string) => {
    const cardValues = hand.split("");

    const jokerCount = (hand.match(/J/g) || []).length;

    const cardCounts = cardValues.reduce((acc, card) => {
        if (acc[card]) {
            acc[card] += 1;
        } else {
            acc[card] = 1;
        }

        return acc;
    }, {});

    const cardCountValues = Object.entries(cardCounts).map(card =>
        card[0] === "J" ? card[1] : (card[1] as number) + jokerCount
    ) as number[];

    if (cardCountValues.includes(5)) {
        return handValues["Five of a kind"];
    }

    if (cardCountValues.includes(4)) {
        return handValues["Four of a Kind"];
    }

    if (cardCountValues.includes(3)) {
        if (
            cardCountValues.length === 2 &&
            cardCountValues.indexOf(3) === cardCountValues.lastIndexOf(3)
        ) {
            return handValues["Full House"];
        }
        if (
            cardCountValues.indexOf(3) !== cardCountValues.lastIndexOf(3) &&
            cardCountValues.length === 3
        )
            return handValues["Full House"];
        else return handValues["Three of a Kind"];
    }

    if (cardCountValues.includes(2)) {
        const pairCount = cardCountValues.filter(count => count === 2).length;

        if (pairCount === 2) {
            return handValues["Two Pair"];
        }

        return handValues["One Pair"];
    }

    return handValues["High Card"];
};

interface Line {
    hand: string;
    bid: number;
}

interface SortedLine extends Line {
    value: number;
}

const main = async () => {
    const data = fs.readFileSync("../../resources/Day07/antoine", "utf8");
    const lines: Line[] = data
        .split("\n")
        .filter(line => line !== "")
        .map(line => {
            const [hand, bid] = line.split(" ");

            return { hand, bid: parseInt(bid) };
        });
    const sorted: SortedLine[] = [];
    lines.forEach(line => {
        sorted.push({ value: getHandValue(line.hand), hand: line.hand, bid: line.bid });
    });
    sorted.sort((a, b) => {
        if (a.value > b.value) {
            return 1;
        }

        if (a.value < b.value) {
            return -1;
        }

        if (a.value === b.value) {
            for (let i = 0; i < 5; i++) {
                if (cards[a.hand[i]] > cards[b.hand[i]]) {
                    return 1;
                }
                if (cards[a.hand[i]] < cards[b.hand[i]]) {
                    return -1;
                }
            }
        }

        return 0;
    });

    const res = sorted.reduce((acc, line, index) => {
        acc += line.bid * (index + 1);
        return acc;
    }, 0);

    console.log("Res: ", res);
};

main();
