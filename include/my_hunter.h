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

typedef struct frames_keys_s {
    bool z;
    bool q;
    bool s;
    bool d;
} frames_keys_t;

typedef struct textured_rect_s {
    sfTexture *texture;
    sfRectangleShape *rectangle;
    sfVector2f size;
    sfVector2f position;
    float angle;
} textured_rect_t;


typedef struct assets_s {
    sfFont *font;
    sfRenderWindow *window;
    textured_rect_t background;
    textured_rect_t new_button;
    sfText *play_btn;
    float heartbeat;
} assets_t;
/***          / FUNCTIONS \        ***/
/*
** Display Functions
*/

void init(assets_t *assets);
void display_menu(assets_t *assets);
void display_background(assets_t *assets);
int display_help(void);
void render_view(int current_view, assets_t *assets);
sfRenderWindow *create_window(int x, int y, char *title);
void handlekeys(sfEvent *event, frames_keys_t *keys);
void handle_resize(sfRenderWindow *window);
void manage_events(sfRenderWindow *window,
    sfEvent *event, frames_keys_t *keys);

sfVector2f calculate_center(sfVector2f *view_size,
    sfVector2f *rectangle_size);


#endif /* !MY_HUNTER_ */
