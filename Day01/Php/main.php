<?php

function openFile($filename)
{
    $file = fopen($filename, "r");

    if (!$file)
        return "";

    $fileContent = fread($file, filesize($filename));
    fclose($file);

    return $fileContent;
}

function getFirstNumber($input, $wordsToFind)
{
    for ($i = 0; $i < strlen($input); $i++) {
        if (ctype_digit($input[$i]))
            return $input[$i];

        foreach ($wordsToFind as $index => $word)
            if (substr($input, $i, strlen($word)) == $word)
                return $index + 1;
    }

    return -1;
}

function getLastNumber($input, $wordsToFind)
{
    for ($i = strlen($input) - 1; $i >= 0; $i--) {
        if (ctype_digit($input[$i]))
            return $input[$i];

        foreach ($wordsToFind as $index => $word)
            if (substr($input, $i - strlen($word), strlen($word)) == $word)
                return $index + 1;
    }

    return -1;
}

function parseArray($input)
{
    $data = explode("\n", $input);
    $res = 0;
    $wordsToFind = array("one", "two", "three", "four", "five", "six", "seven", "eight", "nine");

    for ($i = 0; $i < count($data); $i++) {
        if ($data[$i] != "") {
            $first = getFirstNumber($data[$i], $wordsToFind);
            $second = getLastNumber($data[$i], $wordsToFind);

            if ($first != -1 && $second != -1)
                $res += intval($first . $second);
        }
    }

    return $res;
}

$input = openFile("data.txt");

if ($input == "") {
    echo "Error: File not found\n";
    return -1;
}

echo parseArray($input) . "\n";

return 0;
