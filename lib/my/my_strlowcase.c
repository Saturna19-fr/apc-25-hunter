/*
** EPITECH PROJECT, 2025
** my_strlowcase.c
** File description:
** my_strlowcase.c
*/
#include "include/my.h"

char *my_strlowcase(char *str)
{
    for (int i = 0; i <= my_strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
    }
    return str;
}
