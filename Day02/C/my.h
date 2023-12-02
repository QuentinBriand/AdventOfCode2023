/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #define MAX_BLUE 14
    #define MAX_GREEN 13
    #define MAX_RED 12
    #define NB_COLOR 3
    #define IS_DIGIT(c) c >= '0' && c <= '9'

typedef struct min_cube {
    int min_g;
    int min_r;
    int min_b;
}cube_t;

#endif /* !MY_H_ */
