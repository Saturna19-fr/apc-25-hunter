/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** my_hunter
*/

#ifndef MY_HUNTER_
    #include <stdbool.h>
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include "my.h"


    #define MY_HUNTER_
    #define GAME_AUTHOR "thibault.morez@epitech.eu"
    #define GAME_NAME "MyHunter"
    #define GAME_DESCRIPTION "This game is in progress."
    #define MAX_FRAMERATE 60
    #define _DEBUG 1
    #define BASE_WINDOW_X 1920
    #define BASE_WINDOW_Y 1080
    #define SPRITE_TEXTURE_SIZE 110
    #define SUCCESS 0
    #define FAILURE 84

typedef struct sprites_s {
    sfSprite *duck;
    sfVector2f position;
} sprites_t;

typedef struct background_s {
    sfTexture *texture;
    sfRectangleShape *rectangle;
} background_t;

typedef struct window_s {
    sfRenderWindow *window;
    sfVector2f size;
} window_t;

typedef struct components {
    window_t window;
    sprites_t *sprites;
    background_t background;
} components_t;

/***          / FUNCTIONS \        ***/
/*
** Create Functions
*/

sfRenderWindow *create_window(int x, int y, char *title);

/*
** Create Functions
*/

int display_help(void);

/*
** Display Functions
*/

int display_background(window_t *window, background_t *background);

#endif /* !MY_HUNTER_ */
