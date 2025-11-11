/*
** EPITECH PROJECT, 2025
** my_strncmp.c
** File description:
** strncmp
*/
#include "include/my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int spaces;
    char dumps1[my_strlen(s1)];
    char dumps2[my_strlen(s2)];

    my_strncpy(dumps1, s1, n);
    my_strncpy(dumps2, s2, n);
    spaces = my_strcmp(dumps1, dumps2);
    return spaces;
}
