/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "double.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    #define IS_DIGIT(c) c >= '0' && c <= '9'

typedef struct coord_s {
    int i;
    int j;
} coord_t;

void destroy_nodes(list_t *list);

#endif /* !MY_H_ */
