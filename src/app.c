/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** app.c : creation et destruction de l'application
*/

#include "game.h"
#include "ui.h"

#include <string.h>

static bool load_assets(assets_t *assets)
{
    assets->font = sfFont_createFromFile(FONT_PATH);
    assets->duck_tex = sfTexture_createFromFile(DUCK_PATH, NULL);
    assets->bg_tex = sfTexture_createFromFile(BG_PATH, NULL);
    if (assets->font == NULL || assets->duck_tex == NULL
        || assets->bg_tex == NULL)
        return false;
    assets->duck = sfSprite_create(assets->duck_tex);
    assets->bg = sfSprite_create(assets->bg_tex);
    assets->text = sfText_create(assets->font);
    assets->rect = sfRectangleShape_create();
    assets->circle = sfCircleShape_create();
    return assets->duck != NULL && assets->bg != NULL && assets->text != NULL
        && assets->rect != NULL && assets->circle != NULL;
}

static void setup_assets(assets_t *assets)
{
    sfVector2u bg_size = sfTexture_getSize(assets->bg_tex);
    sfVector2f bg_scale = {
        WORLD_W / (float)bg_size.x, WORLD_H / (float)bg_size.y};
    sfVector2u duck_size = sfTexture_getSize(assets->duck_tex);
    sfVector2f duck_origin = {
        (float)duck_size.y / 2.0f, (float)duck_size.y / 2.0f};
    sfVector2f aim_origin = {AIM_RADIUS, AIM_RADIUS};

    sfSprite_setScale(assets->bg, bg_scale);
    sfSprite_setOrigin(assets->duck, duck_origin);
    sfCircleShape_setRadius(assets->circle, AIM_RADIUS);
    sfCircleShape_setOrigin(assets->circle, aim_origin);
    sfCircleShape_setFillColor(assets->circle, sfTransparent);
    sfCircleShape_setOutlineThickness(assets->circle, AIM_THICKNESS);
}

bool app_create(app_t *app)
{
    memset(app, 0, sizeof(app_t));
    app->window = create_window();
    app->view = sfView_createFromRect(SCREEN_BOX);
    app->clock = sfClock_create();
    if (app->window == NULL || app->view == NULL || app->clock == NULL
        || !load_assets(&app->assets))
        return false;
    setup_assets(&app->assets);
    sfRenderWindow_setView(app->window, app->view);
    sfRenderWindow_setMouseCursorVisible(app->window, false);
    str_copy(app->name, DEFAULT_NAME, NAME_LEN);
    str_copy(app->host, DEFAULT_HOST, HOST_LEN);
    app->iface_count = ifaces_list(app->ifaces, MAX_IFACES);
    return true;
}

static void destroy_assets(assets_t *assets)
{
    sfCircleShape_destroy(assets->circle);
    sfRectangleShape_destroy(assets->rect);
    sfText_destroy(assets->text);
    sfSprite_destroy(assets->bg);
    sfSprite_destroy(assets->duck);
    sfTexture_destroy(assets->bg_tex);
    sfTexture_destroy(assets->duck_tex);
    sfFont_destroy(assets->font);
}

void app_destroy(app_t *app)
{
    net_close(&app->net);
    destroy_assets(&app->assets);
    sfClock_destroy(app->clock);
    sfView_destroy(app->view);
    if (app->window != NULL)
        sfRenderWindow_destroy(app->window);
}
