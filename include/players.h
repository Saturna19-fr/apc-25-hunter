/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** players.h
*/

#ifndef PLAYERS_H_
    #define PLAYERS_H_
    #include <stdbool.h>

    #define MAX_PLAYERS 4
    #define NAME_LEN 14

typedef struct player_s {
    bool used;
    char name[NAME_LEN];
    int score;
    float cx;
    float cy;
} player_t;

#endif /* !PLAYERS_H_ */
