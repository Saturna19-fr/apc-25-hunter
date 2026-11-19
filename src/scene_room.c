/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** scene_room.c : salon d'attente et ecran de fin de manche
*/

#include "ui.h"

static const button_t START_BUTTON = {
    {{660, 800}, {600, 90}}, "Lancer la partie"};
static const button_t AGAIN_BUTTON = {{{660, 800}, {600, 90}}, "Rejouer"};
static const button_t QUIT_BUTTON = {{{810, 920}, {300, 70}}, "Quitter"};
static const sfVector2f TITLE_POS = {CENTER_X, 60};
static const sfVector2f HINT_POS = {CENTER_X, 200};
static const sfVector2f LINE_POS = {CENTER_X, 250};
static const sfVector2f LIST_POS = {680, 430};
static const sfVector2f CHIP_SIZE = {40, 40};
static const float LIST_STEP = 80;
static const float CHIP_SHIFT = 8;
static const float NAME_SHIFT = 64;
static const float SCORE_SHIFT = 460;
static const unsigned int TITLE_SIZE = 96;
static const unsigned int LINE_SIZE = 72;
static const unsigned int TEXT_SIZE = 34;
static const unsigned int ROW_SIZE = 44;

static int best_player(const world_t *world)
{
    const player_t *players = world->players;
    int best = -1;
    bool tie = false;

    for (int id = 0; id < MAX_PLAYERS; id++) {
        if (!players[id].used)
            continue;
        if (best >= 0 && players[id].score == players[best].score)
            tie = true;
        if (best < 0 || players[id].score > players[best].score) {
            best = id;
            tie = false;
        }
    }
    return tie ? -1 : best;
}

static void draw_result(app_t *app)
{
    int best = best_player(&app->world);
    char line[LINE_LEN];
    label_t title = {"Fin de la manche", TITLE_POS, TITLE_SIZE, sfWhite};
    label_t result = {line, LINE_POS, LINE_SIZE, player_color(best)};
    int pos = 0;

    if (best < 0) {
        str_append(line, 0, "Égalité !");
    } else {
        pos = str_append(line, 0, "Victoire de ");
        pos = str_append(line, pos, app->world.players[best].name);
        str_append(line, pos, " !");
    }
    draw_label(app, &title, true);
    draw_label(app, &result, true);
}

static void draw_lobby(app_t *app)
{
    char line[LINE_LEN];
    char port[NB_LEN];
    int pos = str_append(line, 0, app->net.local.address);
    label_t title = {"Salon", TITLE_POS, TITLE_SIZE, sfWhite};
    label_t hint = {"Adresse à donner aux autres joueurs :", HINT_POS,
        TEXT_SIZE, COLOR_MUTED};
    label_t address = {line, LINE_POS, LINE_SIZE, COLOR_ACCENT};

    if (app->net.role == NET_CLIENT) {
        hint.str = "En attente du lancement de la partie par l'hôte...";
        line[0] = '\0';
    } else if (app->net.port != NET_PORT) {
        nb_to_str(app->net.port, port);
        pos = str_append(line, pos, ":");
        str_append(line, pos, port);
    }
    draw_label(app, &title, true);
    draw_label(app, &hint, true);
    draw_label(app, &address, true);
}

static void draw_row(app_t *app, int id, int row)
{
    const player_t *player = &app->world.players[id];
    bool me = id == app->net.my_id;
    float y = LIST_POS.y + (float)row * LIST_STEP;
    char score[NB_LEN];
    sfFloatRect chip = {{LIST_POS.x, y + CHIP_SHIFT}, CHIP_SIZE};
    label_t name = {
        player->name, {LIST_POS.x + NAME_SHIFT, y}, ROW_SIZE, sfWhite};
    label_t value = {
        score, {LIST_POS.x + SCORE_SHIFT, y}, ROW_SIZE, player_color(id)};

    nb_to_str(player->score, score);
    if (app->world.phase != PHASE_END)
        str_copy(score, me ? "(toi)" : "", NB_LEN);
    draw_box(app, &chip, player_color(id), me ? sfWhite : sfTransparent);
    draw_label(app, &name, false);
    draw_label(app, &value, false);
}

void room_draw(app_t *app)
{
    sfFloatRect screen = SCREEN_BOX;
    bool end = app->world.phase == PHASE_END;
    int row = 0;

    draw_box(app, &screen, COLOR_OVERLAY, sfTransparent);
    if (end)
        draw_result(app);
    else
        draw_lobby(app);
    for (int id = 0; id < MAX_PLAYERS; id++) {
        if (app->world.players[id].used) {
            draw_row(app, id, row);
            row++;
        }
    }
    if (app->net.role == NET_HOST)
        button_draw(app, end ? &AGAIN_BUTTON : &START_BUTTON);
    button_draw(app, &QUIT_BUTTON);
}

void room_click(app_t *app)
{
    if (app->net.role == NET_HOST && button_hover(app, &START_BUTTON))
        world_start(&app->world);
    else if (button_hover(app, &QUIT_BUTTON))
        session_leave(app, NULL);
}
