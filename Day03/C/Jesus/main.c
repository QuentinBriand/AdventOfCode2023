/*
** EPITECH PROJECT, 2023
** AdventOfCode2023
** File description:
** main
*/

#include "./include/my.h"

static int count_line(char const *buf)
{
    int count = 0;

    for (int i = 0; buf[i] != '\0'; i++) {
        if (buf[i] == '\n')
            count++;
    }
    return count;
}

static char **load_2d_array(char *buf)
{
    int nb_line = count_line(buf);
    char *token = strtok(buf, "\n");
    char **map = malloc(sizeof(char *) * (nb_line + 1));
    int i = 0;

    map[nb_line] = NULL;
    while (token) {
        map[i] = malloc(sizeof(char) * (strlen(token) + 1));
        memset(map[i], '\0', sizeof(char) * (strlen(token) + 1));
        strcpy(map[i], token);
        i++;
        token = strtok(NULL, "\n");
    }
    return map;
}

static void destroy_file(char **file)
{
    for (int i = 0; file[i]; i++)
        free(file[i]);
    free(file);
}

static coord_t *create_coord(int i, int j)
{
    coord_t *new = malloc(sizeof(coord_t));

    new->i = i;
    new->j = j;
    return new;
}

static int already_use(list_t *list, coord_t coord)
{
    for (list_t *tmp = list; tmp; tmp = tmp->next) {
        if (((coord_t *)tmp->data)->i == coord.i &&
            ((coord_t *)tmp->data)->j == coord.j)
            return 1;
    }
    return 0;
}

static int get_number(char **map, coord_t c, int destroy, int *count)
{
    static list_t *used = NULL;
    int res = 0;
    int len = 0;
    char *number = NULL;

    if (destroy) {
        destroy_nodes(used);
        return destroy_list(&used), 0;
    }
    while (c.j > 0 && IS_DIGIT(map[c.i][c.j - 1]))
        c.j--;
    if (already_use(used, (coord_t){c.i, c.j}))
        return 1;
    while (map[c.i][c.j + len] != '\0' && IS_DIGIT(map[c.i][c.j + len]))
        len++;
    number = strndup(&map[c.i][c.j], len);
    res = atoi(number);
    *count += 1;
    push_front(&used, create_coord(c.i, c.j), OTHER);
    return free(number), res;
}

static int diagonals_find(char **map, int i, int j, int *count)
{
    int res = 1;

    if (i > 0 && j > 0 && IS_DIGIT(map[i - 1][j - 1]))
        res *= get_number(map, (coord_t) {i - 1, j - 1}, 0, count);
    if (i > 0 && map[i][j + 1] != '\0' && IS_DIGIT(map[i - 1][j + 1]))
        res *= get_number(map, (coord_t) {i - 1, j + 1}, 0, count);
    if (map[i + 1] && map[i][j + 1] != '\0' && IS_DIGIT(map[i + 1][j + 1]))
        res *= get_number(map, (coord_t) {i + 1, j + 1}, 0, count);
    if (map[i + 1] && j > 0 && IS_DIGIT(map[i + 1][j - 1]))
        res *= get_number(map, (coord_t) {i + 1, j - 1}, 0, count);
    return res;
}

static int find_number(int i, int j, char **map)
{
    int res = 1;
    int count = 0;

    if (i > 0 && IS_DIGIT(map[i - 1][j]))
        res *= get_number(map, (coord_t) {i - 1, j}, 0, &count);
    if (map[i + 1] && IS_DIGIT(map[i + 1][j]))
        res *= get_number(map, (coord_t) {i + 1, j}, 0, &count);
    if (j > 0 && IS_DIGIT(map[i][j - 1]))
        res *= get_number(map, (coord_t) {i, j - 1}, 0, &count);
    if (map[i][j + 1] && IS_DIGIT(map[i][j + 1]))
        res *= get_number(map, (coord_t) {i, j + 1}, 0, &count);
    res *= diagonals_find(map, i, j, &count);
    if (count < 2)
        return 0;
    return res;
}

static int map_check(char **map)
{
    int i = 0;
    int j = 0;
    int res = 0;

    while (map[i]) {
        if (j == (int)strlen(map[i])) {
            j = 0;
            i++;
            continue;
        }
        if (map[i][j] == '*')
            res += find_number(i, j, map);
        j++;
    }
    return res;
}

int main(void)
{
    int fd = open("./resources/Day03/longInput", O_RDONLY);
    struct stat sb;
    char *buf = NULL;
    char **file = NULL;

    stat("./resources/Day03/longInput", &sb);
    buf = malloc(sizeof(char) * (sb.st_size + 1));
    memset(buf, '\0', sizeof(char) * (sb.st_size + 1));
    read(fd, buf, sb.st_size);
    file = load_2d_array(buf);
    free(buf);
    close(fd);
    printf("%d\n", map_check(file));
    destroy_file(file);
    get_number(NULL, (coord_t) {0, 0}, 1, NULL);
    return 0;
}
