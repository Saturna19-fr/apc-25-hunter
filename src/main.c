/*
** EPITECH PROJECT, 2025
** G-MUL-100
** File description:
** main
*/

#include "../include/my_hunter.h"

int gameloop(components_t *components)
{
    while (sfRenderWindow_isOpen(components->window.window)) {
        sfRenderWindow_clear(components->window.window, sfBlack);
        display_background(&components->window, &components->background);
        sfRenderWindow_display(components->window.window);
    }
    return SUCCESS;
}

int display_background(window_t *window, background_t *background)
{
    my_printf("Displaying background\n");
    printf("Address of background: %p\n\n", &background);
    printf("Address of Window: %p\n\n", &window->window);
    sfRenderWindow_drawRectangleShape(
        window->window,
        background->rectangle,
        NULL
    );
    return SUCCESS;
}


int create_background(background_t *background)
{
    background->rectangle = sfRectangleShape_create();
    background->texture = sfTexture_createFromFile(
        "assets/images/bg.jpg",
        NULL
    );
    sfRectangleShape_setTexture(
        background->rectangle,
        background->texture,
        sfTrue
    );
    sfRectangleShape_setSize(background->rectangle, (sfVector2f) {1920, 1080});
    if (!background->rectangle || !background->texture) {
        my_printf("An erorr occured while creating the background.");
        return FAILURE;
    }
    return SUCCESS;
}

/// @brief Creates the basic components of the game
/// @return SUCCESS or FAILURE
int init_game(void)
{
    components_t components;

    components.window = (window_t) {
        create_window(BASE_WINDOW_X, BASE_WINDOW_Y, GAME_NAME),
        (sfVector2f){BASE_WINDOW_X, BASE_WINDOW_Y}
    };

    create_background(&(components.background));
    gameloop(&components);
    return SUCCESS;
}

int main(int argc, char **argv)
{
    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    return init_game();
}
