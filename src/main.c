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

static sfRenderWindow *create_window(int x, int y, char *title)
{
    sfRenderWindow *window;
    sfVideoMode mode = {x, y, 32};

    window = sfRenderWindow_create(mode, title, sfResize | sfClose, NULL);
    if (window)
        return window;
    return NULL;
}

static void handlekeys(sfEvent *event, frames_keys_t *keys)
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
    sfVector2u min_size = {800, 600};

    sfRenderWindow_setSize(window, min_size);
}

void manage_events(sfRenderWindow *window, sfEvent *event, frames_keys_t *keys)
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

static void display_background(sfRenderWindow *window, char *image_path)
{
    sfTexture *texture = sfTexture_createFromFile(image_path, NULL);
    sfSprite *background;

    if (!texture && _DEBUG)
        my_printf("An error occured while loading file %s.\n", image_path);
    background = sfSprite_create();
    sfSprite_setTexture(background, texture, sfTrue);
    sfRenderWindow_drawSprite(window, background, NULL);
}

static int display_help(void)
{
    my_printf("%s [%s]\n", GAME_NAME, GAME_AUTHOR);
    my_printf("%s\n", GAME_DESCRIPTION);
    return 0;
}

int main(int argc, char **argv)
{
    sfRenderWindow *window;
    sfEvent event;
    frames_keys_t keys;

    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    window = create_window(800, 600, "Test");
    if (window == NULL)
        return 84;
    sfRenderWindow_setFramerateLimit(window, MAX_FRAMERATE);
    while (sfRenderWindow_isOpen(window)) {
        manage_events(window, &event, &keys);
        display_background(window, "images/background.jpg");
        sfRenderWindow_display(window);
        sfRenderWindow_clear(window, sfBlack);
    }
    sfRenderWindow_destroy(window);
}
