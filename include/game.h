/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** game.h : application, scenes et utilitaires
*/

#ifndef GAME_H_
    #define GAME_H_
    #include <CSFML/Graphics.h>
    #include "window.h"
    #include "world.h"
    #include "net.h"

    #define FONT_PATH "assets/fonts/Montserrat-Regular.ttf"
    #define DUCK_PATH "assets/images/spritesheet.png"
    #define BG_PATH "assets/images/bg.jpg"
    #define HOST_LEN 40
    #define NB_LEN 16
    #define BASE_TEN 10
    #define MAX_DT 0.1f
    #define DEFAULT_NAME "Joueur"
    #define DEFAULT_HOST "127.0.0.1"

typedef enum focus_e {
    FOCUS_NAME,
    FOCUS_HOST
} focus_t;

typedef struct assets_s {
    sfFont *font;
    sfTexture *duck_tex;
    sfTexture *bg_tex;
    sfSprite *duck;
    sfSprite *bg;
    sfText *text;
    sfRectangleShape *rect;
    sfCircleShape *circle;
} assets_t;

typedef struct app_s {
    sfRenderWindow *window;
    sfView *view;
    sfClock *clock;
    assets_t assets;
    world_t world;
    net_t net;
    char name[NAME_LEN];
    char host[HOST_LEN];
    focus_t focus;
    iface_t ifaces[MAX_IFACES];
    int iface_count;
    int iface;
    const char *status;
    sfVector2f mouse;
    float anim;
} app_t;

bool app_create(app_t *app);
void app_destroy(app_t *app);
void app_update(app_t *app, float dt);
void app_draw(app_t *app);
void handle_events(app_t *app);

void session_host(app_t *app);
bool session_bind(app_t *app, const char *address);
void session_join(app_t *app);
void session_leave(app_t *app, const char *status);

void menu_draw(app_t *app);
void menu_click(app_t *app);
void menu_text(app_t *app, uint32_t unicode);
void menu_key(app_t *app, sfKeyCode code);
void room_draw(app_t *app);
void room_click(app_t *app);
void game_draw(app_t *app);
void game_click(app_t *app);
void world_draw(app_t *app);
void hud_draw(app_t *app);

void nb_to_str(int nb, char *out);
int str_to_nb(const char *str);
void str_copy(char *dest, const char *src, int max);
int str_append(char *dest, int pos, const char *src);

#endif /* !GAME_H_ */
