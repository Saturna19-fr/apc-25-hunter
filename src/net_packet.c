/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** net_packet.c : encodage et decodage des messages
*/

#include "protocol.h"

static void write_name(sfPacket *packet, const char *name)
{
    bool ended = false;

    for (int i = 0; i < NAME_LEN; i++) {
        ended = ended || name[i] == '\0';
        sfPacket_writeUint8(packet, ended ? 0 : (uint8_t)name[i]);
    }
}

void packet_read_name(sfPacket *packet, char *name)
{
    uint8_t c = 0;

    for (int i = 0; i < NAME_LEN; i++) {
        c = sfPacket_readUint8(packet);
        name[i] = (c == 0 || (c >= ' ' && c <= '~')) ? (char)c : '?';
    }
    name[NAME_LEN - 1] = '\0';
    if (name[0] == '\0') {
        name[0] = '?';
        name[1] = '\0';
    }
}

void packet_write_hello(sfPacket *packet, const char *name)
{
    sfPacket_clear(packet);
    sfPacket_writeUint8(packet, MSG_HELLO);
    write_name(packet, name);
}

void packet_write_input(sfPacket *packet, uint8_t type, float x, float y)
{
    sfPacket_clear(packet);
    sfPacket_writeUint8(packet, type);
    sfPacket_writeFloat(packet, x);
    sfPacket_writeFloat(packet, y);
}

static void write_ducks(sfPacket *packet, const world_t *world)
{
    const duck_t *duck = NULL;

    for (int i = 0; i < MAX_DUCKS; i++) {
        duck = &world->ducks[i];
        sfPacket_writeUint8(packet, duck->state);
        sfPacket_writeUint8(packet, duck->killer);
        sfPacket_writeFloat(packet, duck->x);
        sfPacket_writeFloat(packet, duck->y);
        sfPacket_writeFloat(packet, duck->vx);
        sfPacket_writeFloat(packet, duck->vy);
    }
}

void packet_write_state(sfPacket *packet, const world_t *world, int id)
{
    const player_t *player = NULL;

    sfPacket_clear(packet);
    sfPacket_writeUint8(packet, MSG_STATE);
    sfPacket_writeUint8(packet, (uint8_t)id);
    sfPacket_writeUint8(packet, world->phase);
    sfPacket_writeFloat(packet, world->time_left);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        player = &world->players[i];
        sfPacket_writeBool(packet, player->used);
        write_name(packet, player->name);
        sfPacket_writeInt32(packet, player->score);
        sfPacket_writeFloat(packet, player->cx);
        sfPacket_writeFloat(packet, player->cy);
    }
    write_ducks(packet, world);
}

static void read_players(sfPacket *packet, world_t *world)
{
    player_t *player = NULL;

    for (int i = 0; i < MAX_PLAYERS; i++) {
        player = &world->players[i];
        player->used = sfPacket_readBool(packet);
        packet_read_name(packet, player->name);
        player->score = sfPacket_readInt32(packet);
        player->cx = sfPacket_readFloat(packet);
        player->cy = sfPacket_readFloat(packet);
    }
}

static void read_ducks(sfPacket *packet, world_t *world)
{
    duck_t *duck = NULL;

    for (int i = 0; i < MAX_DUCKS; i++) {
        duck = &world->ducks[i];
        duck->state = sfPacket_readUint8(packet) % DUCK_STATE_COUNT;
        duck->killer = sfPacket_readUint8(packet) % MAX_PLAYERS;
        duck->x = sfPacket_readFloat(packet);
        duck->y = sfPacket_readFloat(packet);
        duck->vx = sfPacket_readFloat(packet);
        duck->vy = sfPacket_readFloat(packet);
    }
}

bool packet_read_state(sfPacket *packet, world_t *world, int *id)
{
    world_t next = *world;
    uint8_t my_id = sfPacket_readUint8(packet);

    next.phase = sfPacket_readUint8(packet) % PHASE_COUNT;
    next.time_left = sfPacket_readFloat(packet);
    read_players(packet, &next);
    read_ducks(packet, &next);
    if (!sfPacket_canRead(packet))
        return false;
    *world = next;
    *id = my_id % MAX_PLAYERS;
    return true;
}
