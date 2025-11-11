/*
** EPITECH PROJECT, 2025
** Flag C
** File description:
** Flag C
*/
#include <stdarg.h>
#include "include/my.h"

int manage_flag_c(va_list args)
{
    return my_putchar(va_arg(args, int));
}
