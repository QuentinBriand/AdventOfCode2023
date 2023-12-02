/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

static int get_nb_cube(char *line)
{
    int i = 0;
    char *number = NULL;
    int res = 0;
    int j = 0;

    for (; line[i] == ' '; i++);
    j = i;
    while (IS_DIGIT(line[j]))
        j++;
    number = strndup(line + i, j - i);
    res = atoi(number);
    free(number);
    return res;
}

static void verify_nb_cube(char *color, int nb_cube, cube_t *cube)
{
    if (strcmp(color, "green") == 0) {
        cube->min_g = nb_cube > cube->min_g ? nb_cube : cube->min_g;
        return;
    }
    if (strcmp(color, "blue") == 0) {
        cube->min_b = nb_cube > cube->min_b ? nb_cube : cube->min_b;
        return;
    }
    if (strcmp(color, "red") == 0) {
        cube->min_r = nb_cube > cube->min_r ? nb_cube : cube->min_r;
        return;
    }
}

void verify_gamble(char *gamble, cube_t *cube)
{
    char *token2 = strtok(gamble, ",");
    int nb = 0;
    int i = 0;

    while (token2) {
        nb = get_nb_cube(token2);
        for (; token2[i] == ' '; i++);
        for (; IS_DIGIT(token2[i]); i++);
        for (; token2[i] == ' '; i++);
        verify_nb_cube(token2 + i, nb, cube);
        token2 = strtok(NULL, ",");
        i = 0;
    }
}

int check_game(char *line)
{
    int i = 0;
    char *token = NULL;
    char *save = NULL;
    cube_t cube = {0, 0, 0};

    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';
    for (; line[i] != ':'; i++);
    line += i + 1;
    token = strtok_r(line, ";", &save);
    while (token) {
        verify_gamble(token, &cube);
        token = strtok_r(NULL, ";", &save);
    }
    return cube.min_b * cube.min_g * cube.min_r;
}

int main(void)
{
    FILE *file = fopen("./resources/Day02/longInput", "r");
    char *buf = NULL;
    int s = 0;
    int res = 0;
    size_t size = 1;

    s = getline(&buf, &size, file);
    while (s != -1) {
        res += check_game(buf);
        s = getline(&buf, &size, file);
    }
    free(buf);
    fclose(file);
    printf("%d\n", res);
    return 0;
}
