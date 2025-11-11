/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** flag_d_i.c
*/

#include <stdarg.h>
#include "include/my.h"

char convert_to_lowercase(char c)
{
    if (c >= 65 && c <= 90) {
        return c + 32;
    }
    return c;
}

int display_hex(char *hexarray, int to_lowercase, int i)
{
    char c;
    int written = 0;

    for (int j = i; j > 0; j--) {
        if (to_lowercase == 1) {
            c = convert_to_lowercase(hexarray[j]);
            written += write(1, &c, 1);
        } else {
            c = hexarray[j];
            written += write(1, &c, 1);
        }
    }
    return written;
}

int convert_to_hex(int nb, int to_lowercase)
{
    char hexarray[100];
    int i = 0;
    int reste;

    while (nb != 0) {
        reste = nb % 16;
        if (reste >= 10) {
            reste = reste + 55;
        } else {
            reste = reste + 48;
        }
        i++;
        hexarray[i] = reste;
        nb = nb / 16;
    }
    return display_hex(hexarray, to_lowercase, i);
}

int manage_flag_x_upper(va_list args)
{
    return convert_to_hex((int) va_arg(args, int), 0);
}

int manage_flag_x(va_list args)
{
    return convert_to_hex((int) va_arg(args, int), 1);
}
