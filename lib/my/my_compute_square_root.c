/*
** EPITECH PROJECT, 2025
** my_compute_square_root
** File description:
** my_compute_square_root
*/
#include "include/my.h"

int my_compute_square_root(int nb)
{
    int current_test = 0;

    for (int i = 1; i <= nb; i++) {
        current_test = my_compute_power_rec(i, 2);
        if (current_test == nb) {
            return i;
        }
    }
    return 0;
}
