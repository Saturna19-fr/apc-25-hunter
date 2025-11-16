/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40 [SSH: phoenix.airplane-pomano.ts.net]
** File description:
** display_funcs.c
*/

#include "../include/my_hunter.h"

void display_background(assets_t *assets)
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

int display_help(void)
{
    my_printf("%s [%s]\n", GAME_NAME, GAME_AUTHOR);
    my_printf("%s\n", GAME_DESCRIPTION);
    return 0;
}

void move_text_inside_center_of_rect(sfRectangleShape *rectangle, sfText *text)
{
    sfFloatRect textBounds = sfText_getLocalBounds(text);
    sfVector2f rectSize = sfRectangleShape_getSize(rectangle);
    sfVector2f rectPos = sfRectangleShape_getPosition(rectangle);

    sfText_setOrigin(
        text,
        (sfVector2f){
            textBounds.left + textBounds.width / 2,
            textBounds.top + textBounds.height / 2
        }
    );
    sfText_setPosition(
        text,
        (sfVector2f){
            rectPos.x + rectSize.x / 2,
            rectPos.y + rectSize.y / 2
        }
    );
}

void display_menu(assets_t *assets)
{
    sfVector2f rectsize = sfRectangleShape_getSize(
        assets->new_button.rectangle
    );
    sfVector2f view_size = sfView_getSize(
        sfRenderWindow_getView(assets->window));

    sfRectangleShape_setPosition(assets->new_button.rectangle,
        calculate_center(&view_size, &rectsize));
    sfRenderWindow_drawRectangleShape(assets->window,
        assets->new_button.rectangle, NULL);
    move_text_inside_center_of_rect(assets->new_button.rectangle,
        assets->play_btn);
    sfRenderWindow_drawText(assets->window,
        assets->play_btn,
        NULL);
}

void render_view(int current_view, assets_t *assets)
{
    if (current_view == 0) {
        display_menu(assets);
    }
    sfRenderWindow_display(assets->window);
}
