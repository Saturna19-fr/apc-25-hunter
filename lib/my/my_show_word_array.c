/*
** EPITECH PROJECT, 2025
** my_str_to_word_array.c
** File description:
** my_show_word_array.c
*/
#include "include/my.h"

void my_show_word_array(char *const *tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        my_putstr(tab[i]);
        my_putchar('\n');
    }
    return;
}
