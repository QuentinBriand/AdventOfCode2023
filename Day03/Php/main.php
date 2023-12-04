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

function getNb($map, $i, $j): int
{
    $res = "";
    while ($j >= 0 && ctype_digit($map[$i][$j])) $j--;
    $j++;

    while ($j < strlen($map[$i]) && ctype_digit($map[$i][$j])) {
        $res .= $map[$i][$j];
        $j++;
    }
    return intval($res);
}

function checkGear($map, $i, $j): int
{
    $data = array();

    for ($k = $i - 1; $k <= $i + 1; $k++) {
        if ($k < 0 || $k >= count($map))
            continue;
        for ($l = $j - 1; $l <= $j + 1; $l++) {
            if ($l < 0 || $l >= strlen($map[$k]))
                continue;
            if ($k == $i && $l == $j)
                continue;
            if (ctype_digit($map[$k][$l])) {
                $tmp = getNb($map, $k, $l);
                if (!in_array($tmp, $data))
                    $data[] = $tmp;
            }
        }
    }

    if (count($data) < 2)
        return 0;

    $res = 1;
    for ($k = 0; $k < count($data); $k++)
        $res *= $data[$k];
    return $res;
}

function getGear($map, $lineIndex): int
{
    $res = 0;
    for ($j = 0; $j < strlen($map[$lineIndex]); $j++) {
        if ($map[$lineIndex][$j] != '*')
            continue;
        $res += checkGear($map, $lineIndex, $j);
    }
    return $res;
}

function parseArray($input): int
{
    $data = explode("\n", $input);
    $res = 0;

    for ($i = 0; $i < count($data); $i++)
        $res += getGear($data, $i);

    return $res;
}

$input = openFile("../../resources/Day03/longInput");
if ($input == "") {
    echo "Error: File not found\n";
    return -1;
}

print parseArray($input) . "\n";

return 0;
