/*
** EPITECH PROJECT, 2025
** my_is_prime
** File description:
** my_is_prime
*/

#include "include/my.h"

int my_is_prime(int nb)
{
    int divisibles_par = 0;

    if (nb <= 1) {
        return 0;
    }
    for (int i = 1; i <= nb; i++) {
        if (nb % i == 0) {
            divisibles_par++;
        }
        if (divisibles_par > 2) {
            return 0;
        }
    }
    return 1;
}
