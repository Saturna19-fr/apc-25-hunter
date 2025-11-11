/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** main.c
*/

#include "include/my.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int handle_flags(va_list args, char *c)
{
    int printed_chars = 0;
    int found = 0;

    for (int i = 0; fcts[i].flag != '\0'; i++) {
        if (fcts[i].flag == *c) {
            printed_chars += (*fcts[i].fptr)(args);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        printed_chars += -2147483648;
    }
    return printed_chars;
}

int my_printf(char *str, ...)
{
    va_list args;
    int result = 0;

    va_start(args, str);
    for (; *str != '\0'; str++) {
        if (*str == '%') {
            str++;
            result += handle_flags(args, str);
        } else {
            result += my_putchar(*str);
        }
    }
    va_end(args);
    if (result < 0) {
        return -1;
    }
    return result;
}
