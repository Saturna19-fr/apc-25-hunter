/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** flag_d_i.c
*/

#include <stdarg.h>
#include "include/my.h"
#include "include/my_macro_abs.h"
#include <stdio.h>

int manage_flag_u(va_list args)
{
    int nb = va_arg(args, int);
    unsigned int result;

    nb = ABS(nb);
    result = (unsigned int) nb;
    return my_put_nbr((int) result, 10);
}
