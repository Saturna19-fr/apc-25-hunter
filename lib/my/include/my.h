/*
** EPITECH PROJECT, 2025
** Header file
** File description:
** header file
*/

#ifndef _MY_H_
    #define _MY_H_
    #include <stdarg.h>
    #include <unistd.h>
    #include <stddef.h>
    #include <limits.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #define UNUSED(x) (void)x
int my_compute_power_rec(int nb, int p);
int my_compute_square_root(int nb);
int my_is_prime(int nb);
int my_put_nbr(int nb, int base);
int my_putchar(char c);
int my_putstr(char const *str);
char *my_revstr(char *str);
int is_alpha(char c);
char **my_str_to_word_array(char *str);
char *my_strcat(char *s1, char *s2);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(const char *str, char const *to_find);
char *my_strupcase(char *str);
void my_swap(int *a, int *b);

int my_getnbr(char const *str);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
void my_sort_int_array(int *tab, int size);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isprintable(char const *str);
int my_str_isupper(char const *str);
char *my_strcapitalize(char *str);
char *my_strncat(char *dest, char const *src, int nb);


char **create_char_array_of_size(int size);
int count_words_valid(char *str);
int parse_all_chars(char **tableau, char *str);
void populate_array(char **array, int index, char c);

#endif //_MY_H
