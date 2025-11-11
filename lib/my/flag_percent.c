/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** flag_d_i.c
*/

#include <stdarg.h>
#include "include/my.h"

int manage_flag_percent(va_list args)
{
    UNUSED(args);
    return my_putchar('%');
}
