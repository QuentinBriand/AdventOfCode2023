import * as fs from "fs";

const compute = (time: number, distance: number) => {
    const delta = time * time - -4 * -distance;
    let s1 = (-time + Math.sqrt(delta)) / -2;
    let s2 = (-time - Math.sqrt(delta)) / -2;

    s1 = s1 % 1 !== 0 ? Math.ceil(s1) + 1 : s1 + 1;
    s2 = s2 % 1 !== 0 ? Math.floor(s2) + 1 : s2 - 1;

    return s2 - s1 + 1;
};

const main = async () => {
    const data = fs.readFileSync("../../resources/Day06/antoine", "utf8");
    const lines = data.split("\n");
    const times = lines[0]
        .split(" ")
        .splice(1)
        .filter(x => x !== "")
        .map(x => parseInt(x));
    const distances = lines[1]
        .split(" ")
        .splice(1)
        .filter(x => x !== "")
        .map(x => parseInt(x));

    let part1 = 1;
    times.forEach((time, index) => {
        part1 *= compute(time, distances[index]);
    });
    console.log("Part 1: ", part1);

    let part2 = 0;
    const part2Time = Number(times.join(""));
    const part2Distances = Number(distances.join(""));
    console.log("Part 2: ", compute(part2Time, part2Distances));
};

main();
