/*
** EPITECH PROJECT, 2025
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/
#include "include/my.h"

char **create_char_array_of_size(int size)
{
    char **array_of_char = malloc(sizeof(char *) * (size + 1));

    for (int i = 0; i < size; i++) {
        array_of_char[i] = "";
    }
    array_of_char[size] = NULL;
    return array_of_char;
}

int count_words_valid(char *str)
{
    int counter = 0;
    int previous = 0;

    for (; *str != '\0'; str++) {
        if (is_alpha(*str) && previous == 0) {
            previous = 1;
        }
        if ((is_alpha(*str) && previous) || (!is_alpha(*str) && !previous)) {
            continue;
        }
        if (!is_alpha(*str) && previous == 1) {
            previous = 0;
            counter++;
        }
    }
    if (previous == 1)
        counter++;
    return counter;
}

int parse_all_chars(char **tableau, char *str)
{
    int counter = 0;
    int previous = 0;

    for (; *str != '\0'; str++) {
        if (is_alpha(*str) && previous == 0) {
            previous = 1;
            populate_array(tableau, counter, *str);
            continue;
        }
        if (is_alpha(*str) && previous) {
            populate_array(tableau, counter, *str);
        }
        if (!is_alpha(*str) && previous == 1) {
            previous = 0;
            counter++;
        }
    }
    if (previous == 1)
        counter++;
    return counter;
}

void populate_array(char **array, int index, char c)
{
    char *current = array[index];

    array[index] = my_strcat(current, &c);
}

char **my_str_to_word_array(char *str)
{
    char **tab = create_char_array_of_size(count_words_valid(str));

    parse_all_chars(tab, str);
    return tab;
}
