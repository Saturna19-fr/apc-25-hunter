/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** scene_game.c : manche en cours (canards, viseurs, scores)
*/

#include "ui.h"

#include <math.h>

static const int DUCK_PX = 110;
static const int DUCK_FRAMES = 3;
static const float ANIM_FPS = 9;
static const float HUD_HEIGHT = 90;
static const float HUD_MARGIN = 50;
static const float HUD_SLOT = 400;
static const float HUD_TEXT_Y = 20;
static const float HUD_NAME_X = 50;
static const float HUD_SCORE_X = 300;
static const sfFloatRect HUD_CHIP = {{0, 28}, {34, 34}};
static const sfVector2f TIMER_POS = {1820, 8};
static const unsigned int HUD_SIZE = 36;
static const unsigned int TIMER_SIZE = 60;

static void draw_duck(app_t *app, const duck_t *duck, int index)
{
    sfSprite *sprite = app->assets.duck;
    bool falling = duck->state == DUCK_FALLING;
    int frame = ((int)(app->anim * ANIM_FPS) + index) % DUCK_FRAMES;
    sfIntRect rect = {{falling ? 0 : frame * DUCK_PX, 0}, {DUCK_PX, DUCK_PX}};
    float zoom = DUCK_SIZE / (float)DUCK_PX;
    sfVector2f scale = {duck->vx < 0 ? -zoom : zoom, falling ? -zoom : zoom};
    sfVector2f pos = {duck->x + DUCK_SIZE / 2.0f, duck->y + DUCK_SIZE / 2.0f};

    sfSprite_setTextureRect(sprite, rect);
    sfSprite_setScale(sprite, scale);
    sfSprite_setColor(sprite, falling ? player_color(duck->killer) : sfWhite);
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(app->window, sprite, NULL);
}

static void draw_score(app_t *app, int id)
{
    const player_t *player = &app->world.players[id];
    float x = HUD_MARGIN + (float)id * HUD_SLOT;
    char score[NB_LEN];
    sfFloatRect chip = HUD_CHIP;
    label_t name = {
        player->name, {x + HUD_NAME_X, HUD_TEXT_Y}, HUD_SIZE, sfWhite};
    label_t value = {
        score, {x + HUD_SCORE_X, HUD_TEXT_Y}, HUD_SIZE, player_color(id)};

    chip.position.x = x;
    nb_to_str(player->score, score);
    draw_box(app, &chip, player_color(id),
        id == app->net.my_id ? sfWhite : sfTransparent);
    draw_label(app, &name, false);
    draw_label(app, &value, false);
}

void hud_draw(app_t *app)
{
    sfFloatRect bar = {{0, 0}, {WORLD_W, HUD_HEIGHT}};
    char seconds[NB_LEN];
    label_t timer = {seconds, TIMER_POS, TIMER_SIZE, COLOR_ACCENT};

    nb_to_str((int)ceilf(app->world.time_left), seconds);
    draw_box(app, &bar, COLOR_PANEL, sfTransparent);
    for (int id = 0; id < MAX_PLAYERS; id++) {
        if (app->world.players[id].used)
            draw_score(app, id);
    }
    draw_label(app, &timer, true);
}

void world_draw(app_t *app)
{
    const world_t *world = &app->world;

    for (int i = 0; i < MAX_DUCKS; i++) {
        if (world->ducks[i].state != DUCK_NONE)
            draw_duck(app, &world->ducks[i], i);
    }
}

void game_draw(app_t *app)
{
    const player_t *player = NULL;
    sfVector2f pos;

    world_draw(app);
    hud_draw(app);
    for (int id = 0; id < MAX_PLAYERS; id++) {
        player = &app->world.players[id];
        if (!player->used || id == app->net.my_id)
            continue;
        pos = (sfVector2f){player->cx, player->cy};
        draw_crosshair(app, pos, player_color(id));
    }
}

void game_click(app_t *app)
{
    if (app->net.role == NET_HOST)
        world_shoot(&app->world, 0, app->mouse.x, app->mouse.y);
    else
        net_client_shoot(&app->net, app->mouse.x, app->mouse.y);
}
