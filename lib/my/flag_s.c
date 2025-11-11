/*
** EPITECH PROJECT, 2025
** flag s
** File description:
** flag s
*/
#include <stdarg.h>
#include "include/my.h"

int manage_flag_s(va_list args)
{
    return my_putstr(va_arg(args, char *));
}
