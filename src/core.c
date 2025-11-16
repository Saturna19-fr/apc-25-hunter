/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40 [SSH: phoenix.airplane-pomano.ts.net]
** File description:
** window.c
*/
#include "../include/my_hunter.h"

sfRenderWindow *create_window(int x, int y, char *title)
{
    sfRenderWindow *window;
    sfVideoMode mode = {x, y, 32};

    window = sfRenderWindow_create(mode, title, sfClose | sfResize, NULL);
    if (window)
        return window;
    return NULL;
}

void handlekeys(sfEvent *event, frames_keys_t *keys)
{
    switch (event->key.code) {
        case sfKeyZ:
            keys->z = true;
            break;
        case sfKeyQ:
            keys->q = true;
            break;
        case sfKeyS:
            keys->s = true;
            break;
        case sfKeyD:
            keys->d = true;
            break;
        default:
            break;
    }
}

void handle_resize(sfRenderWindow *window)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    bool edited = false;

    if (size.x < 800) {
        size.x = 800;
        edited = true;
    }
    if (size.y < 600) {
        size.y = 600;
        edited = true;
    }
    if (edited) {
        sfRenderWindow_setSize(window, size);
    }
}

void manage_events(sfRenderWindow *window,
    sfEvent *event, frames_keys_t *keys)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if ((*event).type == sfEvtClosed)
            sfRenderWindow_close(window);
        if ((*event).type == sfEvtKeyPressed)
            handlekeys(event, keys);
        if ((*event).type == sfEvtResized)
            handle_resize(window);
    }
}
