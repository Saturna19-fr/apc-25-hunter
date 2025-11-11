/*
** EPITECH PROJECT, 2025
** my_swap
** File description:
** Swaps the content of two integers
*/
#include "include/my.h"

void my_swap(int *a, int *b)
{
    int temp = *a;

    *a = *b;
    *b = temp;
}
