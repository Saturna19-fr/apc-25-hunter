/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** draw.c : primitives de dessin (texte, boite, viseur)
*/

#include "ui.h"

#define UTF8_LEAD_MASK 0xE0
#define UTF8_LEAD_TWO 0xC0
#define UTF8_LEAD_BITS 0x1F
#define UTF8_NEXT_BITS 0x3F
#define UTF8_SHIFT 6

static const sfColor PLAYER_COLORS[MAX_PLAYERS] = {{255, 95, 95, 255},
    {90, 175, 255, 255}, {110, 230, 125, 255}, {255, 210, 80, 255}};

sfColor player_color(int id)
{
    if (id < 0 || id >= MAX_PLAYERS)
        return sfWhite;
    return PLAYER_COLORS[id];
}

static void utf8_decode(const char *src, sfChar32 *dest)
{
    const unsigned char *str = (const unsigned char *)src;
    int len = 0;

    for (int i = 0; str[i] != '\0' && len < LABEL_MAX - 1; i++) {
        dest[len] = str[i];
        if ((str[i] & UTF8_LEAD_MASK) == UTF8_LEAD_TWO && str[i + 1] != '\0') {
            dest[len] = ((str[i] & UTF8_LEAD_BITS) << UTF8_SHIFT)
                | (str[i + 1] & UTF8_NEXT_BITS);
            i++;
        }
        len++;
    }
    dest[len] = 0;
}

void draw_label(app_t *app, const label_t *label, bool centered)
{
    sfText *text = app->assets.text;
    sfChar32 buffer[LABEL_MAX];
    sfFloatRect bounds;
    sfVector2f origin = {0.0f, 0.0f};

    utf8_decode(label->str, buffer);
    sfText_setUnicodeString(text, buffer);
    sfText_setCharacterSize(text, label->size);
    sfText_setFillColor(text, label->color);
    bounds = sfText_getLocalBounds(text);
    if (centered)
        origin.x = bounds.position.x + bounds.size.x / 2.0f;
    sfText_setOrigin(text, origin);
    sfText_setPosition(text, label->pos);
    sfRenderWindow_drawText(app->window, text, NULL);
}

void draw_box(app_t *app, const sfFloatRect *box, sfColor fill, sfColor outline)
{
    sfRectangleShape *rect = app->assets.rect;

    sfRectangleShape_setPosition(rect, box->position);
    sfRectangleShape_setSize(rect, box->size);
    sfRectangleShape_setFillColor(rect, fill);
    sfRectangleShape_setOutlineColor(rect, outline);
    sfRectangleShape_setOutlineThickness(rect, outline.a == 0 ? 0 : OUTLINE);
    sfRenderWindow_drawRectangleShape(app->window, rect, NULL);
}

void draw_crosshair(app_t *app, sfVector2f pos, sfColor color)
{
    sfCircleShape *circle = app->assets.circle;
    sfFloatRect dot = {
        {pos.x - AIM_DOT / 2.0f, pos.y - AIM_DOT / 2.0f}, {AIM_DOT, AIM_DOT}};

    sfCircleShape_setPosition(circle, pos);
    sfCircleShape_setOutlineColor(circle, color);
    sfRenderWindow_drawCircleShape(app->window, circle, NULL);
    draw_box(app, &dot, color, sfTransparent);
}
