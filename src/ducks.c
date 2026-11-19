/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** ducks.c : apparition, deplacement et tir sur les canards
*/

#include "world.h"

#include <stdlib.h>

static float rand_range(float min, float max)
{
    return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

static void duck_init(duck_t *duck, float speed)
{
    bool from_left = rand() % 2 == 0;

    duck->state = DUCK_FLYING;
    duck->killer = 0;
    duck->x = from_left ? -DUCK_SIZE : WORLD_W;
    duck->y = rand_range(DUCK_MIN_Y, DUCK_MAX_Y);
    duck->vx = from_left ? speed : -speed;
    duck->vy = rand_range(-DUCK_DRIFT, DUCK_DRIFT);
}

void duck_spawn(world_t *world)
{
    float progress = 1.0f - world->time_left / ROUND_SECONDS;
    float speed = DUCK_SPEED + DUCK_SPEED_GAIN * progress;

    speed += rand_range(0.0f, DUCK_SPEED_RAND);
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (world->ducks[i].state == DUCK_NONE) {
            duck_init(&world->ducks[i], speed);
            return;
        }
    }
}

static void duck_fly(duck_t *duck, float dt)
{
    duck->x += duck->vx * dt;
    duck->y += duck->vy * dt;
    if (duck->y < DUCK_MIN_Y && duck->vy < 0)
        duck->vy = -duck->vy;
    if (duck->y > DUCK_MAX_Y && duck->vy > 0)
        duck->vy = -duck->vy;
    if (duck->x < -DUCK_SIZE || duck->x > WORLD_W)
        duck->state = DUCK_NONE;
}

static void duck_fall(duck_t *duck, float dt)
{
    duck->y += DUCK_FALL_SPEED * dt;
    if (duck->y > WORLD_H)
        duck->state = DUCK_NONE;
}

void ducks_advance(world_t *world, float dt)
{
    for (int i = 0; i < MAX_DUCKS; i++) {
        if (world->ducks[i].state == DUCK_FLYING)
            duck_fly(&world->ducks[i], dt);
        else if (world->ducks[i].state == DUCK_FALLING)
            duck_fall(&world->ducks[i], dt);
    }
}

static bool duck_contains(const duck_t *duck, float x, float y)
{
    if (duck->state != DUCK_FLYING)
        return false;
    if (x < duck->x || x > duck->x + DUCK_SIZE)
        return false;
    return y >= duck->y && y <= duck->y + DUCK_SIZE;
}

bool ducks_hit(world_t *world, int id, float x, float y)
{
    for (int i = MAX_DUCKS - 1; i >= 0; i--) {
        if (duck_contains(&world->ducks[i], x, y)) {
            world->ducks[i].state = DUCK_FALLING;
            world->ducks[i].killer = (uint8_t)id;
            return true;
        }
    }
    return false;
}
