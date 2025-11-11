/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** flag_d_i.c
*/

#include <stdarg.h>
#include "include/my.h"

int manage_flag_i_d(va_list args)
{
    return my_put_nbr((int) va_arg(args, int), 10);
}
