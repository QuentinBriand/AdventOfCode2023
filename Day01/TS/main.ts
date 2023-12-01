import * as fs from "fs";

const digits = [
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine",
];

function is_numeric(c: string): boolean {
  return c >= "0" && c <= "9";
}

function replaceWordNumbers(inputString: string): string[] {
  const wordToNumber: { [key: string]: string } = {
    one: "1",
    two: "2",
    three: "3",
    four: "4",
    five: "5",
    six: "6",
    seven: "7",
    eight: "8",
    nine: "9",
  };

  let test = inputString;

  const indexes = Object.keys(wordToNumber).map((key, i) => {
    const ind = inputString.indexOf(key);
    if (ind != -1) return [ind, i];
    return -1;
  });

  const indexes2 = Object.keys(wordToNumber).map((key, i) => {
    const ind = inputString.lastIndexOf(key);
    if (ind != -1) return [ind, i];
    return -1;
  });

  const min = indexes.filter((i) => i != -1).sort((a, b) => a[0] - b[0])[0];
  const max = indexes2.filter((i) => i != -1).sort((a, b) => b[0] - a[0])[0];

  if (min !== undefined)
    inputString = inputString.replace(
      digits[min[1]],
      wordToNumber[digits[min[1]]]
    );

  if (max !== undefined) {
    const tmp = test.substring(
      test.lastIndexOf(digits[max[1]]) + digits[max[1]].length,
      test.length
    );

    test =
      test.substring(0, test.lastIndexOf(digits[max[1]])) +
      wordToNumber[digits[max[1]]] +
      tmp;
  }
  return [inputString, test];
}

function findInt(str: string): number {
  let res = 0;
  const strs = replaceWordNumbers(str);
  str = strs[0];
  let tmp = strs[1];

  for (let i = 0; i < str.length; i++) {
    if (is_numeric(str[i])) {
      res += parseInt(str[i]) * 10;
      break;
    }
  }

  for (let i = tmp.length - 1; i >= 0; i--) {
    if (is_numeric(tmp[i])) {
      res += parseInt(tmp[i]);
      break;
    }
  }

  return res;
}

const main = async () => {
  const data = await fs.readFileSync(
    "../../resources/Day01/firstInput",
    "utf8"
  );

  const lines = data.split("\n");
  let res = 0;

  lines.forEach((line) => {
    if (line === "") return;
    res += findInt(line);
  });

  console.log(res);
};

main();
