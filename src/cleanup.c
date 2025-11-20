/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** cleanup
*/
#include "../include/my_hunter.h"

void cleanup(components_t *components)
{
    sfRectangleShape_destroy(components->background.rectangle);
    sfTexture_destroy(components->background.texture);
    for (int i = 0; i < MAX_SPRITE_DISPLAYED; i++) {
        sfSprite_destroy(components->sprites[i].duck);
    }
    free(components->sprites);
    sfClock_destroy(components->clock);
}
