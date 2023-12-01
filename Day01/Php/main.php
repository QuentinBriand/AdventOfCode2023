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

function getNumbers($input, $wordsToFind)
{
    $res = array(-1, -1);

    for ($i = 0, $j = strlen($input) - 1; $i < strlen($input) && ($res[0] == -1 || $res[1] == -1); $i++, $j--) {

        if (ctype_digit($input[$i]) && $res[0] == -1)
            $res[0] = $input[$i];
        if (ctype_digit($input[$j]) && $res[1] == -1)
            $res[1] = $input[$j];

        foreach ($wordsToFind as $index => $word) {
            if (substr($input, $i, strlen($word)) == $word && $res[0] == -1)
                $res[0] = $index + 1;
            if (substr($input, $j - strlen($word) + 1, strlen($word)) == $word && $res[1] == -1)
                $res[1] = $index + 1;
        }
    }
    if ($res[0] == -1 || $res[1] == -1)
        return "";
    return $res[0] . $res[1];
}

function parseArray($input)
{
    $data = explode("\n", $input);
    $res = 0;
    $wordsToFind = array("one", "two", "three", "four", "five", "six", "seven", "eight", "nine");
    for ($i = 0; $i < count($data); $i++) {
        if ($data[$i] == "" || ($nb = getNumbers($data[$i], $wordsToFind)) == "")
            continue;
        $res += intval($nb);
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
