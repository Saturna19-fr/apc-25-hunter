/*
** EPITECH PROJECT, 2025
** my_revstr
** File description:
** reverses a string
*/
#include "include/my.h"

char *my_revstr(char *str)
{
    int nb = my_strlen(str);
    char final[nb + 1];
    int perso = 0;

    for (int i = nb - 1; i >= 0; i--) {
        final[perso] = str[i];
        perso++;
    }
    final[nb] = '\0';
    for (int a = 0; a <= nb; a++) {
        str[a] = final[a];
    }
    return str;
}
