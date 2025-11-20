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

int display_background(window_t *window, background_t *background)
{
    const sfView *view = sfRenderWindow_getView(window->window);

    sfRectangleShape_setSize(background->rectangle,
        sfView_getSize(view));
    sfRenderWindow_drawRectangleShape(
        window->window,
        background->rectangle,
        NULL
    );
    return SUCCESS;
}
