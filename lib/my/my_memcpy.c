/*
** EPITECH PROJECT, 2025
** libmy
** File description:
** my_memcpy
*/
#include "include/my.h"

void my_memcpy(void *dest, void *src, size_t n)
{
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (int i = 0; (size_t) i < n; i++) {
        cdest[i] = csrc[i];
    }
}
