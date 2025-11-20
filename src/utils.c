/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** utils
*/
#include "../include/my_hunter.h"

void handle_resize(sfRenderWindow *window)
{
    sfVector2u size = sfRenderWindow_getSize(window);
    bool edited = false;

    if (size.x < MIN_WIDTH) {
        size.x = MIN_WIDTH;
        edited = true;
    }
    if (size.y < MIN_HEIGHT) {
        size.y = MIN_HEIGHT;
        edited = true;
    }
    if (edited) {
        sfRenderWindow_setSize(window, size);
    }
}

int my_random(int min, int max)
{
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void reinit_based_on_score(components_t *components, int score)
{
    for (int i = 0; i <= score; i++) {
        if (!components->sprites[i].initialized) {
            initialize_sprite(components, i);
        }
    }
}
