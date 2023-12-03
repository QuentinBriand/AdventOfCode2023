/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** destroy
*/

#include "./include/my.h"

void destroy_nodes(list_t *list)
{
    for (list_t *tmp = list; tmp; tmp = tmp->next) {
        free(tmp->data);
    }
}
