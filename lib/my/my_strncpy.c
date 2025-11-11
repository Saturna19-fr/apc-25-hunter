/*
** EPITECH PROJECT, 2025
** my_strncpy
** File description:
** my_strncpy.c
*/
#include "include/my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int iter = 0;
    int nmax = my_strlen(src);

    for (iter = 0; iter < n; iter++) {
        dest[iter] = src[iter];
    }
    if (n > nmax) {
        dest[iter] = '\0';
    }
    return dest;
}
