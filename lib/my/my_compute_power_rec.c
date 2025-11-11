/*
** EPITECH PROJECT, 2025
** my_compute_power_rec
** File description:
** my_compute_power_rec
*/
#include "include/my.h"

int my_compute_power_rec(int nb, int p)
{
    int last;

    if (p == 0) {
        return 1;
    }
    if (p < 0) {
        return 0;
    }
    last = my_compute_power_rec(nb, p - 1);
    if (last * nb > 2147483647) {
        return 0;
    }
    return last * nb;
}
