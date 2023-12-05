import * as fs from "fs";

interface range {
    from: number;
    to: number;
    range: number;
}

interface allMaps {
    soilBySeedId: range[];
    fertilizerIdBySoilId: range[];
    waterIdByFertilizerId: range[];
    lightIdByWaterId: range[];
    temperatureIdByLightId: range[];
    humidityIdByTemperatureId: range[];
    locationIdByHumidityId: range[];
}

const maps: allMaps = {
    soilBySeedId: [],
    fertilizerIdBySoilId: [],
    waterIdByFertilizerId: [],
    lightIdByWaterId: [],
    temperatureIdByLightId: [],
    humidityIdByTemperatureId: [],
    locationIdByHumidityId: [],
};

function between(x: number, min: number, max: number) {
    return x >= min && x <= max;
}

const findInMap = (map: range[], value: number) => {
    let res = 0;
    let found = false;
    map.forEach(range => {
        if (found) {
            return;
        }
        if (between(value, range.from, range.from + range.range - 1)) {
            res = range.to + (value - range.from);
            found = true;
            return;
        } else {
            res = value;
        }
    });
    return res;
};

const main = async () => {
    const data = fs.readFileSync("../../resources/Day05/antoine", "utf8");

    const categories = data.split("\n\n");
    const seeds = categories[0].split(" ").slice(1);

    const seedRanges: number[][] = [];

    for (let i = 0; i < seeds.length; i += 2) {
        seedRanges.push([parseInt(seeds[i]), parseInt(seeds[i + 1])]);
    }
    Object.keys(maps).forEach((key, index) => {
        const category = categories[index + 1];
        const indices = category
            .split("\n")
            .slice(1)
            .filter(x => x !== "");
        indices.forEach((index, i) => {
            const [to, from, range] = index.split(" ");
            const fromInt = parseInt(from);
            const toInt = parseInt(to);
            const rangeInt = parseInt(range);
            maps[key][i] = { from: fromInt, to: toInt, range: rangeInt };
        });
    });

    const finalSeeds = seeds.map(seed => {
        const seedId = parseInt(seed);
        const soilId = findInMap(maps.soilBySeedId, seedId);
        const fertilizerId = findInMap(maps.fertilizerIdBySoilId, soilId);
        const waterId = findInMap(maps.waterIdByFertilizerId, fertilizerId);
        const lightId = findInMap(maps.lightIdByWaterId, waterId);
        const temperatureId = findInMap(maps.temperatureIdByLightId, lightId);
        const humidityId = findInMap(maps.humidityIdByTemperatureId, temperatureId);
        const locationId = findInMap(maps.locationIdByHumidityId, humidityId);
        return locationId;
    });
    console.log("Part 1: ", finalSeeds.sort((a, b) => a - b)[0]);

    let finalSeed2 = Infinity;

    for (let i = 0; i < seedRanges.length; i++) {
        const [from, to] = seedRanges[i];
        for (let j = from; j < from + to; j++) {
            const seedId = j;
            const soilId = findInMap(maps.soilBySeedId, seedId);
            const fertilizerId = findInMap(maps.fertilizerIdBySoilId, soilId);
            const waterId = findInMap(maps.waterIdByFertilizerId, fertilizerId);
            const lightId = findInMap(maps.lightIdByWaterId, waterId);
            const temperatureId = findInMap(maps.temperatureIdByLightId, lightId);
            const humidityId = findInMap(maps.humidityIdByTemperatureId, temperatureId);
            const locationId = findInMap(maps.locationIdByHumidityId, humidityId);
            finalSeed2 = Math.min(finalSeed2, locationId);
        }
        console.log("Finished seed range", i);
    }
    console.log("Part 2: ", finalSeed2);
};

main();
