import * as fs from "fs";

const computeDiff = (list: number[]) => {
    const newList = [];
    for (let i = 0; i < list.length - 1; i++) {
        newList.push(list[i + 1] - list[i]);
    }
    return newList;
};

const computeDiff2 = (list: number[]) => {
    const newList = [];
    for (let i = list.length - 1; i <=0; i--) {
        newList.push(list[i] - list[i - 1]);
    }
    return newList;
};

const checkIfLastStep = (list: number[]) => {
    return list.every(value => value === 0);
};

const sequence = (list: number[]) => {
    if (checkIfLastStep(list) === true) return 0;

    const diffs = computeDiff(list);
    return list[list.length - 1] + sequence(diffs);
};

const sequence2 = (list: number[]) => {
    if (checkIfLastStep(list) === true) return 0;

    const diffs = computeDiff2(list);
    return list[0] + sequence(diffs);
};

const main = async () => {
    const data = fs.readFileSync("../../resources/Day09/antoine", "utf8");
    const lines = data
        .split("\n")
        .filter(line => line !== "")
        .map(line => line.split(" ").map(line => parseInt(line)));

    let res = 0;
    let res2 = 0;
    lines.forEach(line => {
        res += sequence(line);
        res2 += sequence(line.reverse());
    });
    console.log(res);
    console.log(res2);
};

main();
