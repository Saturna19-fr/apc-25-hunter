/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** window.c : fenetre et repartition des evenements
*/

#include "game.h"

sfRenderWindow *create_window(void)
{
    sfVideoMode mode = {{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_BPP};
    sfRenderWindow *window = sfRenderWindow_create(
        mode, WINDOW_TITLE, sfResize | sfClose, sfWindowed, NULL);

    if (window == NULL)
        return NULL;
    sfRenderWindow_setFramerateLimit(window, WINDOW_FPS);
    return window;
}

static void update_mouse(app_t *app)
{
    sfVector2i pixel = sfMouse_getPositionRenderWindow(app->window);
    sfVector2f pos =
        sfRenderWindow_mapPixelToCoords(app->window, pixel, app->view);

    if (pos.x < 0.0f)
        pos.x = 0.0f;
    if (pos.x > WORLD_W)
        pos.x = WORLD_W;
    if (pos.y < 0.0f)
        pos.y = 0.0f;
    if (pos.y > WORLD_H)
        pos.y = WORLD_H;
    app->mouse = pos;
}

static void keep_min_size(app_t *app, sfVector2u size)
{
    if (size.x >= WINDOW_MIN_WIDTH && size.y >= WINDOW_MIN_HEIGHT)
        return;
    if (size.x < WINDOW_MIN_WIDTH)
        size.x = WINDOW_MIN_WIDTH;
    if (size.y < WINDOW_MIN_HEIGHT)
        size.y = WINDOW_MIN_HEIGHT;
    sfRenderWindow_setSize(app->window, size);
}

static void on_click(app_t *app)
{
    if (app->net.role == NET_NONE)
        menu_click(app);
    else if (app->world.phase == PHASE_GAME)
        game_click(app);
    else
        room_click(app);
}

static void on_key(app_t *app, sfKeyCode code)
{
    if (app->net.role == NET_NONE)
        menu_key(app, code);
    else if (code == sfKeyEscape)
        session_leave(app, NULL);
}

static void on_event(app_t *app, const sfEvent *event)
{
    if (event->type == sfEvtClosed)
        sfRenderWindow_close(app->window);
    if (event->type == sfEvtResized)
        keep_min_size(app, event->size.size);
    if (event->type == sfEvtMouseButtonPressed
        && event->mouseButton.button == sfMouseLeft)
        on_click(app);
    if (event->type == sfEvtKeyPressed)
        on_key(app, event->key.code);
    if (event->type == sfEvtTextEntered && app->net.role == NET_NONE)
        menu_text(app, event->text.unicode);
}

void handle_events(app_t *app)
{
    sfEvent event;

    update_mouse(app);
    while (sfRenderWindow_pollEvent(app->window, &event))
        on_event(app, &event);
}
