/*
** EPITECH PROJECT, 2025
** G-MUL-100
** File description:
** main
*/

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include "../include/my_hunter.h"
#include "../include/my.h"
#include <stddef.h>

sfRenderWindow *create_window(int x, int y, char *title)
{
    sfRenderWindow *window;
    sfVideoMode mode = {x, y, 32};

    window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    if (window)
        return window;
    return NULL;
}

void manage_events(sfRenderWindow *window, sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if ((*event).type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

int display_help(void)
{
    my_printf("%s [%s]\n", GAME_NAME, GAME_AUTHOR);
    my_printf("%s\n", GAME_DESCRIPTION);
    return 0;
}

int main(int argc, char **argv)
{
    sfRenderWindow *window;
    sfEvent event;
    sfUint8 *pixels = malloc((800 * 600 * 32) / 8);

    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    window = create_window(800, 600, "Test");
    if (window == NULL)
        return 84;
    if (pixels == NULL)
        return 84;
    while (sfRenderWindow_isOpen(window)) {
        manage_events(window, &event);
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    sfRenderWindow_destroy(window);
}
