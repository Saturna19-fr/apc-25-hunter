/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40 [SSH: phoenix.airplane-pomano.ts.net]
** File description:
** window.c
*/
#include "../include/my_hunter.h"

static void update_anim(sfClock *clock, sprite_t *s, sfRenderWindow *w)
{
    sfTime t = sfClock_getElapsedTime(clock);
    float sec = t.microseconds / 10000.0;
    sfVector2u sz = sfRenderWindow_getSize(w);

    if (sfSprite_getPosition(s->duck).y == 0)
        sfSprite_setPosition(s->duck,
            (sfVector2f){0, my_random(0, sz.y)});
    if (sec >= 10 && s->is_flying) {
        s->rect.left += 110;
        s->texture_face = s->rect.left % 330;
        if (s->rect.left >= 330) {
            s->rect.left = 0;
            s->texture_face = 0;
        }
        sfSprite_setTextureRect(s->duck, s->rect);
        sfSprite_move(s->duck, (sfVector2f){10, 0});
        sfClock_restart(clock);
    }
}

void animate(sfClock *clock, sprite_t *s, sfRenderWindow *w)
{
    update_anim(clock, s, w);
}

void manage_events(sfRenderWindow *window,
    sfEvent *event)
{
    while (sfRenderWindow_pollEvent(window, event)) {
        if ((*event).type == sfEvtClosed)
            sfRenderWindow_close(window);
        if ((*event).type == sfEvtResized)
            handle_resize(window);
    }
}

void check_mousebuttonclick(components_t *components,
    sprite_t *sprite, int *score)
{
    sfVector2i mousePos;
    sfVector2f worldPos;
    sfFloatRect bounds;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        mousePos = sfMouse_getPositionRenderWindow(
            components->window.window);
        worldPos = sfRenderWindow_mapPixelToCoords(
            components->window.window,
            mousePos,
            NULL);
        bounds = sfSprite_getGlobalBounds(sprite->duck);
        if (sfFloatRect_contains(&bounds, worldPos.x, worldPos.y) &&
            sprite != NULL) {
            (*score)++;
            sprite->is_flying = false;
        }
    }
}

int game(components_t *components, int *score)
{
    sprite_t sprite;

    for (int i = 0; i < MAX_SPRITE_DISPLAYED; i++) {
        sprite = components->sprites[i];
        if (sprite.initialized == true && sprite.is_flying == true) {
            animate(components->clock, &components->sprites[i],
                components->window.window);
            sfRenderWindow_drawSprite(
                components->window.window,
                sprite.duck,
                NULL);
            check_mousebuttonclick(components,
                &components->sprites[i], score);
        }
    }
    return SUCCESS;
}

int gameloop(components_t *components, int *score, int nb_sprt)
{
    UNUSED(nb_sprt);
    while (sfRenderWindow_isOpen(components->window.window)) {
        sfRenderWindow_clear(components->window.window, sfBlack);
        display_background(&components->window, &components->background);
        manage_events(components->window.window, &components->event);
        game(components, score);
        reinit_based_on_score(components, *score);
        sfRenderWindow_display(components->window.window);
        if (*score == MAX_SPRITE_DISPLAYED) {
            sfRenderWindow_close(components->window.window);
            cleanup(components);
        }
    }
    return SUCCESS;
}
