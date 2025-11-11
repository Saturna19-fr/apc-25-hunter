/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** my_putstr file
*/
#include "include/my.h"

int my_putstr(char const *str)
{
    char charx;
    int x = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        charx = str[i];
        x += my_putchar(charx);
    }
    return x;
}
