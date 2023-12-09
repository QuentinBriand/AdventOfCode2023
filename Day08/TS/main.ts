import * as fs from "fs";
import { keyBy, groupBy } from "lodash";

function* getCurrentInstruction(instructions: string[]) {
    let index = 0;

    while (1) {
        if (index >= instructions.length) index = 0;
        yield instructions[index];
        index++;
    }
}

const compute = (currentStep: any, steps: any, iterator: any) => {
    let i = 0;
    while (currentStep.stepId.charAt(2) !== "Z") {
        currentStep = steps[currentStep[iterator.next().value as string]];
        i++;
    }
    return i;
};

const gcd = (a: number, b: number) => {
    if (!b) {
        return a;
    }
    return gcd(b, a % b);
};

const main = async () => {
    const data = fs.readFileSync("../../resources/Day08/antoine", "utf8");
    const lines = data
        .split("\n")
        .filter(line => line !== "")
        .map(line => line.trim());

    const instructions = lines[0].split("");
    let iterator = getCurrentInstruction(instructions);

    const steps = keyBy(
        lines.splice(1).map(step => {
            const splitted = step.split("=");
            const stepId = splitted[0].trim();
            const instruction = splitted[1].split(", ").map(instruction => instruction.trim());
            return { stepId, L: instruction[0].slice(1), R: instruction[1].slice(0, -1) };
        }),
        "stepId"
    );

    // let currentStep = steps["AAA"];
    // let i = 0;
    // while (currentStep.stepId !== "ZZZ") {
    //     currentStep = steps[currentStep[iterator.next().value as string]];
    //     i++;
    // }
    // console.log("Part 1:", i);

    let res2 = 0;
    iterator = getCurrentInstruction(instructions);
    const endingInA = keyBy(
        Object.values(steps).filter(step => step.stepId.charAt(2) === "A"),
        "stepId"
    );
    let nbFinished = 0;

    const currentSteps = Object.values(endingInA).map(step => {
        return { ...step, done: false };
    });

    const nbToFinish = currentSteps.length;
    let nbSteps = 0;

    const distances = currentSteps.map(step => compute(step, steps, iterator));

    let lcm = 1;
    distances.forEach(distance => (lcm = (lcm * distance) / gcd(lcm, distance)));
    console.log(lcm);
    
};

main();
