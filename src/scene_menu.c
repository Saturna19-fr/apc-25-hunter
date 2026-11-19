/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** scene_menu.c : menu principal (pseudo, heberger, rejoindre)
*/

#include "ui.h"

static const sfFloatRect NAME_BOX = {{660, 400}, {600, 72}};
static const sfFloatRect HOST_BOX = {{660, 530}, {600, 72}};
static const sfFloatRect IFACE_BOX = {{660, 660}, {600, 72}};
static const button_t HOST_BUTTON = {{{660, 770}, {285, 90}}, "Héberger"};
static const button_t JOIN_BUTTON = {{{975, 770}, {285, 90}}, "Rejoindre"};
static const sfVector2f IFACE_TITLE_POS = {660, 614};
static const sfVector2f IFACE_TEXT_POS = {CENTER_X, 670};
static const sfVector2f TITLE_POS = {CENTER_X, 70};
static const sfVector2f SUBTITLE_POS = {CENTER_X, 240};
static const sfVector2f STATUS_POS = {CENTER_X, 885};
static const sfVector2f HINT_POS = {CENTER_X, 975};
static const unsigned int TITLE_SIZE = 130;
static const unsigned int TEXT_SIZE = 38;
static const unsigned int HINT_SIZE = 28;

static void draw_texts(app_t *app)
{
    label_t title = {"MY HUNTER", TITLE_POS, TITLE_SIZE, sfWhite};
    label_t subtitle = {"Duck Hunt en réseau - de 2 à 4 joueurs", SUBTITLE_POS,
        TEXT_SIZE, COLOR_ACCENT};
    label_t status = {app->status, STATUS_POS, TEXT_SIZE, COLOR_ERROR};
    label_t hint = {"Un joueur héberge, les autres tapent son adresse puis "
                    "Rejoindre.",
        HINT_POS, HINT_SIZE, COLOR_MUTED};

    draw_label(app, &title, true);
    draw_label(app, &subtitle, true);
    draw_label(app, &hint, true);
    if (app->status != NULL)
        draw_label(app, &status, true);
}

static void draw_selector(app_t *app)
{
    const iface_t *iface = &app->ifaces[app->iface];
    bool hover = sfFloatRect_contains(&IFACE_BOX, app->mouse);
    char line[LINE_LEN];
    int pos = str_append(line, 0, "<   ");
    label_t title = {"Interface d'écoute (pour héberger)", IFACE_TITLE_POS,
        INPUT_TITLE, COLOR_MUTED};
    label_t value = {line, IFACE_TEXT_POS, INPUT_TEXT, sfWhite};

    pos = str_append(line, pos, iface->name);
    pos = str_append(line, pos, "  ");
    pos = str_append(line, pos, iface->address);
    str_append(line, pos, "   >");
    draw_box(app, &IFACE_BOX, COLOR_PANEL, hover ? COLOR_ACCENT : COLOR_MUTED);
    draw_label(app, &title, false);
    draw_label(app, &value, true);
}

static void cycle_iface(app_t *app)
{
    float middle = IFACE_BOX.position.x + IFACE_BOX.size.x / 2.0f;
    int step = app->mouse.x < middle ? -1 : 1;

    app->iface_count = ifaces_list(app->ifaces, MAX_IFACES);
    app->iface = (app->iface + step + app->iface_count) % app->iface_count;
}

void menu_draw(app_t *app)
{
    sfFloatRect screen = SCREEN_BOX;
    input_t name = {NAME_BOX, "Ton pseudo", app->name};
    input_t host = {HOST_BOX, "Adresse de l'hôte (pour rejoindre)", app->host};

    draw_box(app, &screen, COLOR_OVERLAY, sfTransparent);
    draw_texts(app);
    input_draw(app, &name, app->focus == FOCUS_NAME);
    input_draw(app, &host, app->focus == FOCUS_HOST);
    draw_selector(app);
    button_draw(app, &HOST_BUTTON);
    button_draw(app, &JOIN_BUTTON);
}

void menu_click(app_t *app)
{
    if (sfFloatRect_contains(&NAME_BOX, app->mouse))
        app->focus = FOCUS_NAME;
    if (sfFloatRect_contains(&HOST_BOX, app->mouse))
        app->focus = FOCUS_HOST;
    if (sfFloatRect_contains(&IFACE_BOX, app->mouse))
        cycle_iface(app);
    if (button_hover(app, &HOST_BUTTON))
        session_host(app);
    else if (button_hover(app, &JOIN_BUTTON))
        session_join(app);
}

void menu_text(app_t *app, uint32_t unicode)
{
    if (app->focus == FOCUS_NAME)
        input_type(app->name, NAME_LEN, unicode);
    else
        input_type(app->host, HOST_LEN, unicode);
}

void menu_key(app_t *app, sfKeyCode code)
{
    if (code == sfKeyTab)
        app->focus = app->focus == FOCUS_NAME ? FOCUS_HOST : FOCUS_NAME;
    if (code == sfKeyBackspace)
        input_erase(app->focus == FOCUS_NAME ? app->name : app->host);
    if (code == sfKeyEnter && app->focus == FOCUS_HOST)
        session_join(app);
}
