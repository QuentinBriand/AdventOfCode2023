/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "double.h"

    #define IS_DIGIT(c) c >= '0' && c <= '9'

typedef enum step_e {
    SEED_SOIL,
    SOIL_FERTI,
    FERTI_WAT,
    WAT_LIGHT,
    LIGHT_TEMP,
    TEMP_HUM,
    HUM_LOC,
    NB_STEPS
}steps;

typedef struct converter_s {
    unsigned long long born_in;
    unsigned long long born_out;
    unsigned long long range;
}converter_t;

#endif /* !MY_H_ */
