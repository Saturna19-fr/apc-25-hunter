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
    #include <string.h>
    #include <SFML/System/Clock.h>
    #include <SFML/Window.h>
    #include "my.h"


    #define MY_HUNTER_
    #define GAME_AUTHOR "thibault.morez@epitech.eu"
    #define GAME_NAME "MyHunter"
    #define GAME_DESCRIPTION "This game is in progress."
    #define MAX_FRAMERATE 60
    #define DEFAULT_WIDTH 1920
    #define DEFAULT_HEIGHT 1080
    #define MIN_WIDTH 800
    #define MIN_HEIGHT 600
    #define SPRITE_TEXTURE_SIZE 110
    #define SUCCESS 0
    #define FAILURE 84
    #define MAX_SPRITE_DISPLAYED 12

typedef struct sprite_s {
    bool initialized;
    bool is_flying;
    sfSprite *duck;
    int texture_face;
    sfIntRect rect;
    sfVector2f position;
} sprite_t;

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
    sprite_t *sprites;
    background_t background;
    sfEvent event;
    sfClock *clock;
} components_t;

/***          / FUNCTIONS \        ***/
/*
** Create Functions
*/

sfRenderWindow *create_window(int x, int y, char *title);
int create_background(background_t *background);
int create_sprite(sprite_t **sprites);
void initialize_sprite(components_t *components, int sprite);
/*
** Display Functions
*/

int display_help(void);
int display_background(window_t *window, background_t *background);

/*
** Manage functions
*/
void manage_events(sfRenderWindow *window,
    sfEvent *event);
int gameloop(components_t *components, int *score, int nb_sprt);
int init_game(void);
void handle_resize(sfRenderWindow *window);


int my_random(int min, int max);
void cleanup(components_t *components);
void reinit_based_on_score(components_t *components, int score);

#endif /* !MY_HUNTER_ */
