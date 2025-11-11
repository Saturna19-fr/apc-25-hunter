/*
** EPITECH PROJECT, 2025
** my_strstr
** File description:
** the closest implementation of the equivalent to find, standalone ?
*/
#include "include/my.h"

char *my_strstr(const char *str, char const *to_find)
{
    int j = 0;

    if (my_strlen(to_find) > my_strlen(str) || *str == '\0') {
        return NULL;
    }
    if (*to_find == '\0') {
        return (char *) str;
    }
    for (int i = 0; i <= my_strlen(str) - my_strlen(to_find); i++) {
        j = 0;
        while (str[i + j] == to_find[j] && to_find[j] != '\0') {
            j++;
        }
        if (to_find[j] == '\0') {
            return (char *)(str + i);
        }
    }
    return NULL;
}
