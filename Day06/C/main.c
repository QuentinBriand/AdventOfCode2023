/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "my.h"

static void fill_tab(long *tab1, char *rec)
{
    char *token = strtok(rec, " \t");
    int i = 0;

    token = strtok(NULL, " \t");
    while (token) {
        tab1[i] = atoi(token);
        token = strtok(NULL, " \t");
        i++;
    }
}

static int get_roots(int time, size_t delta)
{
    float root1 = ((-time + sqrt(delta)) / -2.0f);
    float root2 = ((-time - sqrt(delta)) / -2.0f);

    root1 += (root1 == (int)root1) ? 1 : 0;
    root2 -= (root2 == (int)root2) ? 1 : 0;
    root1 = ceil(root1);
    root2 = floor(root2);
    return root2 - root1 + 1;
}

static void compute_games(long *times, long *rec, long *res)
{
    int delta = 0;

    for (int i = 0; i < NB_GAME; i++) {
        delta = pow(times[i], 2) - 4 * rec[i];
        if (delta == 0) {
            res[i] = 1;
            continue;
        }
        if (delta > 0) {
            res[i] = get_roots(times[i], delta);
        }
    }
}

static int get_power(int nb)
{
    int power = 0;

    while (nb) {
        power++;
        nb /= 10;
    }
    return power;
}

static void compute_res(long time, long obj)
{
    size_t delta = 0;
    size_t res = 0;

    delta = pow(time, 2) - 4 * obj;
    printf("%ld %ld %lu\n", time, obj, delta);
    if (delta == 0) {
        res = 1;
    } else if (delta > 0) {
        double root1 = ((-time + sqrtl(delta)) / -2.0);
        double root2 = ((-time - sqrtl(delta)) / -2.0);
        printf("%f %f\n", root1, root2);

        root1 += (root1 == (long)root1) ? 1 : 0;
        root2 -= (root2 == (long)root2) ? 1 : 0;
        root1 = ceil(root1);
        root2 = floor(root2);
        res = root2 - root1 + 1;
    }
    printf("Possibility for 2nd step: %lu\n", res);
}

static void compute_one_game(long *times, long *rec)
{
    long time = 0;
    long obj = 0;
    int power_tmp = 0;

    for (int i = NB_GAME - 1; i >= 0; i--) {
        time += times[i] * pow(10, power_tmp);
        power_tmp += get_power(times[i]);
    }
    power_tmp = 0;
    for (int i = NB_GAME - 1; i >= 0; i--) {
        obj += rec[i] * pow(10, power_tmp);
        power_tmp += get_power(rec[i]);
    }
    compute_res(time, obj);
}

static void display_res(long *res)
{
    long nb = res[0];

    for (int i = 1; i < NB_GAME; i++)
        nb *= res[i];
    printf("Possibility: %ld\n", nb);
}

int main(void)
{
    FILE *file = fopen("./resources/Day06/longInput", "r");
    char *times = NULL;
    char *distance = NULL;
    size_t size = 1;
    long tab_times[NB_GAME];
    long tab_dist[NB_GAME];
    long res[NB_GAME] = {0};

    getline(&times, &size, file);
    getline(&distance, &size, file);
    fill_tab(tab_times, times);
    fill_tab(tab_dist, distance);
    compute_games(tab_times, tab_dist, res);
    compute_one_game(tab_times, tab_dist);
    display_res(res);
    free(times);
    free(distance);
    fclose(file);
    return 0;
}
