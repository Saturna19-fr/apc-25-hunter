/*
** EPITECH PROJECT, 2025
** my_str_isalpha
** File description:
** my_str_isalpha
*/
#include "include/my.h"

int is_alpha(char c)
{
    return (c >= 97 && c <= 122) ||
        (c >= 65 && c <= 90) ||
        (c >= 49 && c <= 57);
}
