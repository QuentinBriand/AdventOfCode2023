/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

static converter_t *get_numbers(char *line)
{
    int i = 0;
    unsigned long long tmp[3] = {0};
    converter_t *new = malloc(sizeof(converter_t));
    char *token = strtok(line, " \t");

    while (token) {
        tmp[i] = strtoull(token, NULL, 10);
        i++;
        token = strtok(NULL, " \t");
    }
    new->born_out = tmp[0];
    new->born_in = tmp[1];
    new->range = tmp[2];
    return new;
}

static void build_steps(FILE *file, list_t **table, steps index)
{
    size_t size = 1;
    int s = 0;
    char *buf = NULL;
    converter_t *temp = NULL;

    s = getline(&buf, &size, file);
    while (s > 1) {
        temp = get_numbers(buf);
        push_front(&table[index], temp, OTHER);
        s = getline(&buf, &size, file);
    }
    free(buf);
}

static list_t **fill_tab_list(void)
{
    list_t **table = malloc(sizeof(list_t *) * NB_STEPS);

    for (int i = 0; i < NB_STEPS; i++)
        table[i] = NULL;
    return table;
}

static list_t **build_converter(FILE *file)
{
    int s = 0;
    char *buf = NULL;
    size_t size = 1;
    steps index = SEED_SOIL;
    list_t **table = fill_tab_list();

    s = getline(&buf, &size, file);
    while (s != -1) {
        if (size == 1) {
            s = getline(&buf, &size, file);
            continue;
        }
        if (strlen(buf) > 1 && buf[strlen(buf) - 2] == ':') {
            build_steps(file, table, index);
            index++;
        }
        s = getline(&buf, &size, file);
    }
    return free(buf), table;
}

static unsigned long long step_seed(list_t *list, unsigned long long nb)
{
    converter_t *temp = NULL;

    for (list_t *tmp = list; tmp; tmp = tmp->next) {
        temp = ((converter_t *)tmp->data);
        if (nb >= temp->born_in && nb < temp->born_in + temp->range) {
            return nb - temp->born_in + temp->born_out;
        }
    }
    return nb;
}

static size_t find_pos(list_t **converter, unsigned long long seed, int d)
{
    static size_t pos = 0;
    static int first = 0;
    unsigned long long processing = seed;

    if (d)
        return pos;
    for (steps i = SEED_SOIL; i < NB_STEPS; i++)
        processing = step_seed(converter[i], processing);
    if (!first) {
        pos = processing;
        first++;
    } else
        pos = (processing < pos) ? processing : pos;
    return pos;
}

static void build_seeds(char *seeds, list_t **table)
{
    char *token = strtok(seeds, " \t");
    size_t seed = 0;
    size_t range_seed = 0;

    token = strtok(NULL, " \t");
    while (token) {
        seed = strtoull(token, NULL, 10);
        token = strtok(NULL, " \t");
        range_seed = strtoull(token, NULL, 10);
        for (size_t i = 0; i < range_seed; i++)
            find_pos(table, seed + i, 0);
        token = strtok(NULL, " \t");
    }
}

static void destroy_table(list_t **list)
{
    for (int i = 0; i < NB_STEPS; i++) {
        for (list_t *tmp = list[i]; tmp; tmp = tmp->next)
            free(tmp->data);
        destroy_list(&list[i]);
    }
    free(list);
}

int main(void)
{
    FILE *file = fopen("./resources/Day05/longInput", "r");
    list_t **table = NULL;
    char *seeds = NULL;
    size_t size = 1;

    getline(&seeds, &size, file);
    table = build_converter(file);
    build_seeds(seeds, table);
    printf("res: %lu\n", find_pos(NULL, 0, 1));
    destroy_table(table);
    free(seeds);
    fclose(file);
    return 0;
}
