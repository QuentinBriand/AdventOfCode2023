import * as fs from "fs";

const cubes = [
  { color: "red", number: 12 },
  { color: "green", number: 13 },
  { color: "blue", number: 14 },
];

const checkLine = (line: string) => {
  const [gameNb, rolls] = line.split(":");
  const splittedRolls = rolls.split(";");
  let illegal = false;
  const minimums = {
    red: Infinity,
    green: Infinity,
    blue: Infinity,
  };
  splittedRolls.forEach((roll) => {
    roll = roll.trim();
    const tries = roll.split(", ");
    tries.forEach((try_) => {
      const [number, color] = try_.split(" ");
      if (minimums[color] === Infinity) {
        minimums[color] = Math.min(minimums[color], Number(number));
      } else {
        minimums[color] = Math.max(minimums[color], Number(number));
      }
      const cube = cubes.find((cube) => cube.color === color);
      if (cube && Number(number) > cube.number) {
        illegal = true;
      }
    });
  });
  return [illegal ? 0 : Number(gameNb.split(" ")[1]), minimums];
};

const main = async () => {
  const data = fs.readFileSync("../../resources/Day02/antoine", "utf8");

  const lines = data.split("\n");
  let res1 = 0, res2 = 0;

  lines.forEach((line) => {
    if (line === "" || line === "\n") return;
    const tmp = checkLine(line) as any;
    res1 += tmp[0];
    console.log(tmp);

    res2 += tmp[1].red * tmp[1].green * tmp[1].blue;
  });

  console.log("Part 1", res1);
  console.log("Part 2", res2);
};

main();
