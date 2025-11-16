/*
** EPITECH PROJECT, 2025
** G-MUL-100
** File description:
** main
*/

#include "../include/my_hunter.h"

void init(assets_t *assets)
{
    assets->window = create_window(BASE_WINDOW_X, BASE_WINDOW_Y, "My Hunter");
    assets->background.rectangle = sfRectangleShape_create();
    assets->background.texture = sfTexture_createFromFile(
        "assets/images/background.jpg", NULL);
    assets->new_button.rectangle = sfRectangleShape_create();
    assets->new_button.size = (sfVector2f) {200, 60};
    assets->new_button.position = (sfVector2f) {500, 500};
    sfRectangleShape_setFillColor(assets->new_button.rectangle, sfYellow);
    sfRectangleShape_setSize(assets->new_button.rectangle,
        assets->new_button.size);
    sfRectangleShape_setPosition(assets->new_button.rectangle,
        assets->new_button.position);
    assets->font = sfFont_createFromFile(
        "assets/fonts/Montserrat-Regular.ttf");
    assets->play_btn = sfText_create();
    sfText_setFont(assets->play_btn, assets->font);
    sfText_setString(assets->play_btn, "Play");
    sfText_setColor(assets->play_btn, sfBlack);
}

// static void cleanup(assets_t *assets)
// {
//     sfRectangleShape_destroy(assets->background.rectangle);
//     sfTexture_destroy(assets->background.texture);
//     sfRenderWindow_destroy(assets->window);
// }
sfVector2f calculate_center(sfVector2f *view_size,
    sfVector2f *rectangle_size)
{
    sfVector2f new = {0.0, 0.0};

    new.x = ((*view_size).x / 2) - ((*rectangle_size).x / 2);
    new.y = ((*view_size).y / 2) - ((*rectangle_size).y / 2);
    return new;
}

int main(int argc, char **argv)
{
    sfEvent event;
    frames_keys_t keys;
    assets_t assets;
    int current_view = 0;

    if (argc == 2 && my_strlen(argv[1]) == 2 && argv[1][0] == '-' &&
        argv[1][1] == 'h')
        return display_help();
    init(&assets);
    printf("Init \n");
    if (assets.window == NULL)
        return 84;
    while (sfRenderWindow_isOpen(assets.window)) {
        sfRenderWindow_clear(assets.window, sfBlack);
        manage_events(assets.window, &event, &keys);
        display_background(&assets);
        render_view(current_view, &assets);
    }
    return 0;
}
