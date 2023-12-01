package main

import (
	"fmt"
	"os"
	"bufio"
)

func isDigit(char byte) bool {
	return char >= '0' && char <= '9'
}

func parseLine(line string, words [9]string) [2]int {
	res := [2]int{-1, -1}

	for i, j := 0, len(line)-1; i < len(line) && (res[0] == -1 || res[1] == -1); i, j = i+1, j-1 {
		if isDigit(line[i]) && res[0] == -1 {
			res[0] = int(line[i]) - '0'
		}
		if isDigit(line[j]) && res[1] == -1 {
			res[1] = int(line[j]) - '0'
		}
		for index, word := range words {
			if i+len(word) <= len(line) && line[i:i+len(word)] == word && res[0] == -1 {
				res[0] = index + 1
			}
			if j-len(word)+1 >= 0 && line[j-len(word)+1:j+1] == word && res[1] == -1 {
				res[1] = index + 1
			}
		}
	}
	return res
}

func parseArray(input *bufio.Scanner) int {
	var res int
	words := [9]string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}
	nb := [2]int{-1, -1}
	for input.Scan() {
		var line = input.Text()
		nb = parseLine(line, words)
		if line != "" && nb[0] != -1 && nb[1] != -1 {
			res += ((nb[0] * 10) + nb[1])
		}

	}
	return res
}

func main() {
	fileName := "message.txt"
	file, err := os.Open(fileName)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	var buf = bufio.NewScanner(file)
	if err := buf.Err(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	res := parseArray(buf)
	defer file.Close()
	fmt.Println(res)
}
