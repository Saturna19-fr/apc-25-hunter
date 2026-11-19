/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** loop.c : mise a jour et affichage d'une image
*/

#include "game.h"
#include "ui.h"

static void sync_my_cursor(app_t *app)
{
    int id = app->net.my_id;

    if (app->net.role == NET_NONE || id < 0)
        return;
    app->world.players[id].cx = app->mouse.x;
    app->world.players[id].cy = app->mouse.y;
}

static void update_client(app_t *app, float dt)
{
    if (!net_client_receive(&app->net, &app->world)) {
        session_leave(app, "Connexion perdue avec l'hôte");
        return;
    }
    sync_my_cursor(app);
    net_client_tick(&app->net, &app->world, dt);
    ducks_advance(&app->world, dt);
}

void app_update(app_t *app, float dt)
{
    if (dt > MAX_DT)
        dt = MAX_DT;
    app->anim += dt;
    if (app->net.role == NET_CLIENT)
        update_client(app, dt);
    if (app->net.role == NET_HOST) {
        sync_my_cursor(app);
        net_host_update(&app->net, &app->world, dt);
        world_update(&app->world, dt);
    }
}

void app_draw(app_t *app)
{
    bool online = app->net.role != NET_NONE && app->net.my_id >= 0;

    sfRenderWindow_clear(app->window, sfBlack);
    sfRenderWindow_drawSprite(app->window, app->assets.bg, NULL);
    if (app->net.role == NET_NONE)
        menu_draw(app);
    else if (app->world.phase == PHASE_GAME)
        game_draw(app);
    else
        room_draw(app);
    draw_crosshair(
        app, app->mouse, online ? player_color(app->net.my_id) : sfWhite);
    sfRenderWindow_display(app->window);
}
