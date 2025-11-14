/*
** EPITECH PROJECT, 2025
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** my_hunter
*/

#ifndef MY_HUNTER_
    #include <stdbool.h>
    #define MY_HUNTER_
    #define GAME_AUTHOR "thibault.morez@epitech.eu"
    #define GAME_NAME "MyHunter"
    #define GAME_DESCRIPTION "This game is in progress."
    #define MAX_FRAMERATE 60
    #define _DEBUG 1


typedef struct frames_keys_s {
    bool z;
    bool q;
    bool s;
    bool d;
} frames_keys_t;

typedef struct content_s {
    sfTexture *texture;
    sfRectangleShape *rectangle;
    sfVector2f size;
    float angle;
} content_t;

typedef struct button_s {
    sfText *text;
    sfColor color;
    content_t rect;
} button_t;

typedef struct assets_s {
    sfFont *font;
    sfRenderWindow *window;
    content_t background;
    button_t play_button;
    float heartbeat;
} assets_t;

#endif /* !MY_HUNTER_ */
