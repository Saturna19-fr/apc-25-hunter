/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** world.c : regles d'une manche (cote hote uniquement)
*/

#include "world.h"

#include <string.h>

void world_start(world_t *world)
{
    memset(world->ducks, 0, sizeof(world->ducks));
    for (int i = 0; i < MAX_PLAYERS; i++)
        world->players[i].score = 0;
    world->time_left = ROUND_SECONDS;
    world->spawn_timer = 0.0f;
    world->phase = PHASE_GAME;
}

static void world_finish(world_t *world)
{
    memset(world->ducks, 0, sizeof(world->ducks));
    world->time_left = 0.0f;
    world->phase = PHASE_END;
}

void world_update(world_t *world, float dt)
{
    float progress = 0.0f;

    if (world->phase != PHASE_GAME)
        return;
    world->time_left -= dt;
    if (world->time_left <= 0.0f) {
        world_finish(world);
        return;
    }
    progress = 1.0f - world->time_left / ROUND_SECONDS;
    world->spawn_timer -= dt;
    if (world->spawn_timer <= 0.0f) {
        duck_spawn(world);
        world->spawn_timer = SPAWN_SLOW - (SPAWN_SLOW - SPAWN_FAST) * progress;
    }
    ducks_advance(world, dt);
}

bool world_shoot(world_t *world, int id, float x, float y)
{
    if (world->phase != PHASE_GAME || !ducks_hit(world, id, x, y))
        return false;
    world->players[id].score++;
    return true;
}
