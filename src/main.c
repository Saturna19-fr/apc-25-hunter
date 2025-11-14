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

    window = sfRenderWindow_create(mode, title, sfClose | sfResize, NULL);
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

static void display_background(assets_t *assets)
{
    const sfView *view = sfRenderWindow_getView(assets->window);

    sfRectangleShape_setSize(assets->background.rectangle,
        sfView_getSize(view));
    if (!assets->background.texture && _DEBUG)
        my_printf("[WARN] Background texture not loaded.\n");
    sfRectangleShape_setTexture(assets->background.rectangle,
        assets->background.texture, sfTrue);
    sfRenderWindow_drawRectangleShape(assets->window,
        assets->background.rectangle, NULL);
}

static int display_help(void)
{
    my_printf("%s [%s]\n", GAME_NAME, GAME_AUTHOR);
    my_printf("%s\n", GAME_DESCRIPTION);
    return 0;
}

// typedef struct content_s {
//     sfTexture *texture;
//     sfRectangleShape *rectangle;
//     sfVector2f position;
//     sfVector2f size;
//     float angle;
// } content_t;
void init(assets_t *assets)
{
    assets->window = create_window(800, 600, "My Hunter");
    assets->background.rectangle = sfRectangleShape_create();
    assets->background.texture = sfTexture_createFromFile(
        "images/background.jpg", NULL);
}

void cleanup(assets_t *assets)
{
    sfRectangleShape_destroy(assets->background.rectangle);
    sfTexture_destroy(assets->background.texture);
    sfRenderWindow_destroy(assets->window);
    sfRenderWindow_setFramerateLimit(assets->window, MAX_FRAMERATE);
}

int main(int argc, char **argv)
{
    sfEvent event;
    frames_keys_t keys;
    assets_t assets;

    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    init(&assets);
    if (assets.window == NULL)
        return 84;
    while (sfRenderWindow_isOpen(assets.window)) {
        manage_events(assets.window, &event, &keys);
        display_background(&assets);
        sfRenderWindow_display(assets.window);
    }
    cleanup(&assets);
    return 0;
}

// sfRenderWindow_clear(assets.window, sfBlack);
