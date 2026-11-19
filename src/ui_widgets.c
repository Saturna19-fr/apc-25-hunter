/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** ui_widgets.c : boutons et champs de saisie
*/

#include "ui.h"
#include "my.h"

bool button_hover(const app_t *app, const button_t *button)
{
    return sfFloatRect_contains(&button->box, app->mouse);
}

void button_draw(app_t *app, const button_t *button)
{
    const sfFloatRect *box = &button->box;
    bool hover = button_hover(app, button);
    label_t label = {button->label,
        {box->position.x + box->size.x / 2.0f,
            box->position.y + box->size.y / 2.0f - BUTTON_TEXT * TEXT_SHIFT},
        BUTTON_TEXT, sfWhite};

    draw_box(app, box, hover ? COLOR_HOVER : COLOR_BUTTON, sfWhite);
    draw_label(app, &label, true);
}

void input_draw(app_t *app, const input_t *input, bool focused)
{
    const sfFloatRect *box = &input->box;
    char shown[HOST_LEN + 2];
    bool blink = focused && (int)(app->anim * 2.0f) % 2 == 0;
    label_t title = {input->title,
        {box->position.x, box->position.y - INPUT_TITLE_GAP}, INPUT_TITLE,
        COLOR_MUTED};
    label_t value = {shown,
        {box->position.x + INPUT_PAD,
            box->position.y + box->size.y / 2.0f - INPUT_TEXT * TEXT_SHIFT},
        INPUT_TEXT, sfWhite};

    str_copy(shown, input->value, HOST_LEN);
    if (blink)
        str_append(shown, my_strlen(shown), "_");
    draw_box(app, box, COLOR_PANEL, focused ? COLOR_ACCENT : COLOR_MUTED);
    draw_label(app, &title, false);
    draw_label(app, &value, false);
}

void input_type(char *value, int max, uint32_t unicode)
{
    int len = my_strlen(value);

    if (unicode < ' ' || unicode > '~' || len >= max - 1)
        return;
    value[len] = (char)unicode;
    value[len + 1] = '\0';
}

void input_erase(char *value)
{
    int len = my_strlen(value);

    if (len > 0)
        value[len - 1] = '\0';
}
