<?php

function openFile($filename) : string
{
    $file = fopen($filename, "r");
    if (!$file)
        return "";
    $fileContent = fread($file, filesize($filename));
    fclose($file);
    return $fileContent;
}

function parseSet($set, $picked): array
{
    $data = explode(",", $set);

    $colors = array("red", "green", "blue");

    for ($i = 0; $i < count($data); $i++) {
        $data[$i] = trim($data[$i]);
        foreach ($colors as $index => $color)
            if (str_contains($data[$i], $color)) {
                if (intval(substr($data[$i], 0, 2)) > $picked[$index])
                    $picked[$index] = intval(substr($data[$i], 0, 2));
            }
    }

    return $picked;
}

function parseGame($game): int
{
    $data = explode(":", $game);
    $picked = array(0, 0, 0);
    for ($i = 1; $i < count($data); $i++) {
        $sets = explode(";", $data[$i]);
        for ($j = 0; $j < count($sets); $j++) {
            $picked = parseSet($sets[$j], $picked);
        }
    }
    return $picked[0] * $picked[1] * $picked[2];
}

function parseArray($input) : int
{
    $data = explode("\n", $input);
    $res = 0;

    for ($i = 0; $i < count($data); $i++) {
        if ($data[$i] == "")
            continue;
        $res += parseGame($data[$i]);
    }
    return $res;
}

$input = openFile("../../resources/Day02/example");
if ($input == "") {
    echo "Error: File not found\n";
    return -1;
}

print parseArray($input) . "\n";

return 0;
