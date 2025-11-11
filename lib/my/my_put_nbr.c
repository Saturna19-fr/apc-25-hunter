/*
** EPITECH PROJECT, 2025
** my_put_nbr.c
** File description:
** My Put Number
*/

#include "include/my.h"

int my_put_nbr(int nb, int base)
{
    int written = 0;

    if (nb == INT_MIN) {
        write(1, "-2147483648", 11);
        return 12;
    }
    if (nb < 0) {
        written += my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        written += my_put_nbr(nb / base, base);
    }
    written += my_putchar((nb % base) + '0');
    return written;
}
