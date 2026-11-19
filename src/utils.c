/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** utils.c : petites fonctions de chaines et de nombres
*/

#include "game.h"

void nb_to_str(int nb, char *out)
{
    char digits[NB_LEN];
    unsigned int value = nb < 0 ? -(unsigned int)nb : (unsigned int)nb;
    int len = 0;
    int pos = 0;

    if (nb < 0) {
        out[pos] = '-';
        pos++;
    }
    for (; value > 0 || len == 0; value /= BASE_TEN) {
        digits[len] = (char)('0' + value % BASE_TEN);
        len++;
    }
    for (; len > 0; len--) {
        out[pos] = digits[len - 1];
        pos++;
    }
    out[pos] = '\0';
}

int str_to_nb(const char *str)
{
    int value = 0;

    for (int i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
        value = value * BASE_TEN + (str[i] - '0');
        if (value > NET_PORT_MAX)
            return -1;
    }
    return value;
}

void str_copy(char *dest, const char *src, int max)
{
    int i = 0;

    for (; i < max - 1 && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}

int str_append(char *dest, int pos, const char *src)
{
    for (int i = 0; src[i] != '\0'; i++) {
        dest[pos] = src[i];
        pos++;
    }
    dest[pos] = '\0';
    return pos;
}
