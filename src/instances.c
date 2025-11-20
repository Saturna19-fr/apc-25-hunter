/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** instances
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

int create_sprite(sprite_t **sprites)
{
    size_t memory_needed = sizeof(sprite_t) * MAX_SPRITE_DISPLAYED;
    sprite_t *arr = malloc(memory_needed);
    sprite_t template;

    template.initialized = false;
    template.duck = NULL;
    template.texture_face = 0;
    template.rect = (sfIntRect) {0, 0, 0, 0};
    for (size_t i = 0; i < MAX_SPRITE_DISPLAYED - 1; i++) {
        my_memcpy(&(arr[i]), &template, sizeof(sprite_t));
    }
    template.initialized = false;
    my_memcpy(&(arr[MAX_SPRITE_DISPLAYED - 1]), &template, sizeof(sprite_t));
    *sprites = arr;
    return SUCCESS;
}

void initialize_sprite(components_t *components, int sprite)
{
    sfTexture *texture;

    components->sprites[sprite].initialized = true;
    components->sprites[sprite].duck = sfSprite_create();
    components->sprites[sprite].is_flying = true;
    components->sprites[sprite].rect = (sfIntRect) {0, 0, 110, 110};
    texture = sfTexture_createFromFile(
        "assets/images/spritesheet.png",
        NULL
    );
    sfSprite_setTexture(
        components->sprites[sprite].duck,
        texture,
        sfTrue
    );
    sfSprite_setTextureRect(
        components->sprites[sprite].duck,
        components->sprites[sprite].rect
    );
}

int init_game(void)
{
    int score = 0;
    int number_of_sprites = 0;
    components_t components;

    components.window = (window_t) {
        create_window(DEFAULT_WIDTH, DEFAULT_HEIGHT, GAME_NAME),
        (sfVector2f){DEFAULT_WIDTH, DEFAULT_HEIGHT}
    };
    components.clock = sfClock_create();
    create_background(&(components.background));
    create_sprite(&components.sprites);
    initialize_sprite(&components, 0);
    gameloop(&components, &score, number_of_sprites);
    return SUCCESS;
}
