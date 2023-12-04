/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./include/my.h"

static void fill_win_nb(int *win_nb, char *line)
{
    char *token = strtok(line, " \t");
    int i = 0;

    while (token) {
        win_nb[i] = atoi(token);
        i++;
        token = strtok(NULL, " \t");
    }
    free(line);
}

static int is_in(int *win_nbs, int nb)
{
    for (int j = 0; j < NB_WIN; j++)
        if (nb == win_nbs[j])
            return 1;
    return 0;
}

static void score_points(int *score, int *win_nbs, char *line, cards_t *cards)
{
    char *token = strtok(line, " \t");
    int index_tmp = cards->index + 1;

    while (token) {
        if (is_in(win_nbs, atoi(token))) {
            *score = *score == 0 ? 1 : *score * 2;
            cards->copys[index_tmp] += cards->copys[cards->index];
            index_tmp++;
        }
        token = strtok(NULL, " \t");
    }
}

static int count_point(char *line, cards_t *cards)
{
    int count = 0;
    int winning_nbs[NB_WIN] = {0};
    int score = 0;

    for (; line[0] != ':'; line++);
    line++;
    for (int i = 0; line[i] != '|'; i++)
        count++;
    fill_win_nb(winning_nbs, strndup(line, count));
    line += count + 1;
    score_points(&score, winning_nbs, line, cards);
    cards->index++;
    return score;
}

static int count_line(char *filepath)
{
    FILE *file = fopen(filepath, "r");
    int s = 0;
    char *buf = NULL;
    size_t size = 1;
    int count = 0;

    s = getline(&buf, &size, file);
    while (s != -1) {
        count++;
        s = getline(&buf, &size, file);
    }
    free(buf);
    fclose(file);
    return count;
}

static int sum_tab(int *cards, int size)
{
    int res = 0;

    for (int i = 0; i < size; i++)
        res += cards[i];
    return res;
}

static void fill_tab(int *tab, int nb, int size)
{
    for (int i = 0; i < size; i++)
        tab[i] = nb;
}

int main(void)
{
    FILE *file = fopen("./resources/Day04/longInput", "r");
    char *buf = NULL;
    int s = 0;
    int res = 0;
    int nb_card = count_line("./resources/Day04/longInput");
    cards_t cards = {malloc(sizeof(int) * nb_card), 0};
    size_t size = 1;

    fill_tab(cards.copys, 1, nb_card);
    s = getline(&buf, &size, file);
    while (s != -1) {
        res += count_point(buf, &cards);
        s = getline(&buf, &size, file);
    }
    free(buf);
    fclose(file);
    printf("Part 1: %d, part 2: %d\n", res, sum_tab(cards.copys, nb_card));
    free(cards.copys);
    return 0;
}
