/*
** EPITECH PROJECT, 2025
** G-MUL-100
** File description:
** main
*/

#include "../include/my_hunter.h"

int main(int argc, char **argv)
{
    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    return init_game();
}
