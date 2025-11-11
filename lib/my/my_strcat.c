/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** my_strcat
*/
#include "include/my.h"

char *my_strcat(char *s1, char *s2)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));

    for (int i = 0; s1[i] != '\0'; i++) {
        new_str[i] = s1[i];
    }
    for (int i = 0; s2[i] != '\0'; i++) {
        new_str[i + my_strlen(s1)] = s2[i];
    }
    new_str[(my_strlen(s1) + my_strlen(s2))] = '\0';
    return new_str;
}
