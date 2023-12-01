/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main.c
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

static int is_digit_word(char *line)
{
    char *words[9] = {"one", "two",
        "three", "four", "five", "six",
        "seven", "eight", "nine"
    };
    size_t i = 0;
    int j = 0;

    while (i < strlen(line)) {
        if (j == 9) {
            j = 0;
            i++;
            continue;
        }
        if (strncmp(line, words[j], strlen(words[j])) == 0) {
                return j + 1;
            }
        j++;
    }
    return 0;
}

static int first_digit_compare(char *line, int i, int *res)
{
    int tmp = 0;

    if (IS_DIGIT(line[i])) {
        *res += (line[i] - '0') * 10;
        return 0;
    } else {
        tmp = is_digit_word(&line[i]);
        if (tmp) {
            *res += tmp * 10;
            return 0;
        }
    }
    return 1;
}

static int last_digit_compare(char *line, int end, int *res)
{
    int tmp = 0;

    if (IS_DIGIT(line[end])) {
        *res += (line[end] - '0');
        return 0;
    } else {
        tmp = is_digit_word(&line[end]);
        if (tmp) {
            *res += tmp;
            return 0;
        }
    }
    return 1;
}

static int check_line(char *line)
{
    int end = strlen(line) - 1;
    int res = 0;
    int is_first = 1;
    int is_last = 1;

    for (size_t i = 0; i < strlen(line); i++) {
        if (is_first)
            is_first = first_digit_compare(line, i, &res);
        if (is_last)
            is_last = last_digit_compare(line, end, &res);
        end--;
        if (!is_first && !is_last)
            break;
    }
    return res;
}

int main(void)
{
    FILE *file = fopen("./resources/Day01/firstInput", "r");
    char *buf = NULL;
    int s = 0;
    int res = 0;
    size_t size = 1;

    s = getline(&buf, &size, file);
    while (s != -1) {
        res += check_line(buf);
        s = getline(&buf, &size, file);
    }
    free(buf);
    fclose(file);
    printf("%d\n", res);
    return 0;
}
