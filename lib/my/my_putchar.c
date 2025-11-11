/*
** EPITECH PROJECT, 2025
** my_putchar.c
** File description:
** myputchar.c
*/
#include "include/my.h"

int my_putchar(char c)
{
    if (c != '\0') {
        return write(1, &c, 1);
    }
    return 0;
}
