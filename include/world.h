/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** world.h : simulation du jeu (aucune dependance graphique)
*/

#ifndef WORLD_H_
    #define WORLD_H_
    #include <stdbool.h>
    #include <stdint.h>
    #include "players.h"

    #define WORLD_W 1920.0f
    #define WORLD_H 1080.0f
    #define MAX_DUCKS 16
    #define DUCK_SIZE 160.0f
    #define DUCK_MIN_Y 110.0f
    #define DUCK_MAX_Y 800.0f
    #define DUCK_SPEED 280.0f
    #define DUCK_SPEED_GAIN 420.0f
    #define DUCK_SPEED_RAND 160.0f
    #define DUCK_DRIFT 90.0f
    #define DUCK_FALL_SPEED 900.0f
    #define ROUND_SECONDS 60.0f
    #define SPAWN_SLOW 0.9f
    #define SPAWN_FAST 0.3f

typedef enum phase_e {
    PHASE_LOBBY,
    PHASE_GAME,
    PHASE_END,
    PHASE_COUNT
} phase_t;

typedef enum duck_state_e {
    DUCK_NONE,
    DUCK_FLYING,
    DUCK_FALLING,
    DUCK_STATE_COUNT
} duck_state_t;

typedef struct duck_s {
    uint8_t state;
    uint8_t killer;
    float x;
    float y;
    float vx;
    float vy;
} duck_t;

typedef struct world_s {
    uint8_t phase;
    float time_left;
    float spawn_timer;
    player_t players[MAX_PLAYERS];
    duck_t ducks[MAX_DUCKS];
} world_t;

void world_start(world_t *world);
void world_update(world_t *world, float dt);
bool world_shoot(world_t *world, int id, float x, float y);

void duck_spawn(world_t *world);
void ducks_advance(world_t *world, float dt);
bool ducks_hit(world_t *world, int id, float x, float y);

#endif /* !WORLD_H_ */
