/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40 [SSH: phoenix.airplane-pomano.ts.net]
** File description:
** display_funcs.c
*/

#include "../include/my_hunter.h"

int display_help(void)
{
    my_printf("%s [%s]\n", GAME_NAME, GAME_AUTHOR);
    my_printf("%s\n", GAME_DESCRIPTION);
    return 0;
}
