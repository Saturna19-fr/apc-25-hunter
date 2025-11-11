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
    #define UNUSED(x) (void) x
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

typedef struct functions_table {
    char flag;
    int (*fptr)(va_list);
} fct_table_t;

int my_printf(char *str, ...);


int manage_flag_s(va_list args);
int manage_flag_c(va_list args);
int manage_flag_i_d(va_list args);
int manage_flag_x_upper(va_list args);
int manage_flag_x(va_list args);
int manage_flag_o(va_list args);
int manage_flag_percent(va_list args);
int manage_flag_u(va_list args);

void write_to_stderr(char c);
void string_to_stderr(char *str);

char convert_to_lowercase(char c);
int convert_to_hex(int nb, int to_lowercase);

static const fct_table_t fcts[] = {
    {'c', &manage_flag_c},
    {'s', &manage_flag_s},
    {'d', &manage_flag_i_d},
    {'i', &manage_flag_i_d},
    {'o', &manage_flag_o},
    {'x', &manage_flag_x},
    {'X', &manage_flag_x_upper},
    {'%', &manage_flag_percent},
    {'u', &manage_flag_u},
    {'\0', NULL}
};

#endif
