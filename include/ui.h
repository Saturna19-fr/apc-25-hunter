/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** ui.h : dessin, boutons et champs de saisie
*/

#ifndef UI_H_
    #define UI_H_
    #include "game.h"

    #define COLOR_OVERLAY sfColor_fromRGBA(8, 12, 30, 170)
    #define COLOR_PANEL sfColor_fromRGBA(10, 16, 40, 215)
    #define COLOR_BUTTON sfColor_fromRGBA(36, 70, 160, 235)
    #define COLOR_HOVER sfColor_fromRGBA(70, 120, 235, 255)
    #define COLOR_ACCENT sfColor_fromRGB(255, 210, 80)
    #define COLOR_MUTED sfColor_fromRGB(170, 180, 200)
    #define COLOR_ERROR sfColor_fromRGB(255, 120, 110)
    #define CENTER_X (WORLD_W / 2.0f)
    #define SCREEN_BOX ((sfFloatRect){{0, 0}, {WORLD_W, WORLD_H}})
    #define TEXT_SHIFT 0.65f
    #define LABEL_MAX 128
    #define LINE_LEN 64
    #define OUTLINE 3.0f
    #define AIM_RADIUS 24.0f
    #define AIM_THICKNESS 5.0f
    #define AIM_DOT 6.0f
    #define BUTTON_TEXT 40
    #define INPUT_TEXT 40
    #define INPUT_TITLE 30
    #define INPUT_TITLE_GAP 46.0f
    #define INPUT_PAD 20.0f

typedef struct label_s {
    const char *str;
    sfVector2f pos;
    unsigned int size;
    sfColor color;
} label_t;

typedef struct button_s {
    sfFloatRect box;
    const char *label;
} button_t;

typedef struct input_s {
    sfFloatRect box;
    const char *title;
    const char *value;
} input_t;

sfColor player_color(int id);
void draw_label(app_t *app, const label_t *label, bool centered);
void draw_box(
    app_t *app, const sfFloatRect *box, sfColor fill, sfColor outline);
void draw_crosshair(app_t *app, sfVector2f pos, sfColor color);

bool button_hover(const app_t *app, const button_t *button);
void button_draw(app_t *app, const button_t *button);
void input_draw(app_t *app, const input_t *input, bool focused);
void input_type(char *value, int max, uint32_t unicode);
void input_erase(char *value);

#endif /* !UI_H_ */
