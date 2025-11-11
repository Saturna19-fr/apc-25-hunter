/*
** EPITECH PROJECT, 2025
** my_strupcase.c
** File description:
** strupcase
*/
#include "include/my.h"

char *my_strupcase(char *str)
{
    for (int i = 0; i <= my_strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
    return str;
}
