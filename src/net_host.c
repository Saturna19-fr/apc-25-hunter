/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** net_host.c : l'hote accepte les joueurs et diffuse l'etat du jeu
*/

#include "net.h"
#include "protocol.h"
#include "my.h"

#include <string.h>

bool net_host_start(net_t *net, unsigned short port, const char *address)
{
    sfIpAddress bind = sfIpAddress_fromString(address);

    net->listener = sfTcpListener_create();
    net->in = sfPacket_create();
    if (net->listener == NULL || net->in == NULL
        || sfTcpListener_listen(net->listener, port, bind) != sfSocketDone) {
        net_close(net);
        return false;
    }
    sfTcpListener_setBlocking(net->listener, false);
    net->local = bind;
    if (my_strcmp(address, IFACE_ALL) == 0)
        net->local = sfIpAddress_getLocalAddress();
    net->port = port;
    net->role = NET_HOST;
    net->my_id = 0;
    return true;
}

static int free_slot(const net_t *net)
{
    for (int id = 1; id < MAX_PLAYERS; id++) {
        if (net->peers[id].sock == NULL)
            return id;
    }
    return -1;
}

static void accept_peer(net_t *net, world_t *world)
{
    sfTcpSocket *sock = NULL;
    int id = free_slot(net);

    if (sfTcpListener_accept(net->listener, &sock) != sfSocketDone)
        return;
    if (id < 0) {
        sfTcpSocket_destroy(sock);
        return;
    }
    if (!peer_attach(&net->peers[id], sock))
        return;
    memset(&world->players[id], 0, sizeof(player_t));
    world->players[id].used = true;
    world->players[id].name[0] = '?';
}

static void handle_msg(net_t *net, world_t *world, int id)
{
    player_t *player = &world->players[id];
    uint8_t type = sfPacket_readUint8(net->in);
    float x = 0.0f;
    float y = 0.0f;

    if (type == MSG_HELLO)
        packet_read_name(net->in, player->name);
    if (type != MSG_CURSOR && type != MSG_SHOOT)
        return;
    x = sfPacket_readFloat(net->in);
    y = sfPacket_readFloat(net->in);
    if (!sfPacket_canRead(net->in) || !(x >= 0.0f && x <= WORLD_W)
        || !(y >= 0.0f && y <= WORLD_H))
        return;
    player->cx = x;
    player->cy = y;
    if (type == MSG_SHOOT)
        world_shoot(world, id, x, y);
}

static void receive_peer(net_t *net, world_t *world, int id)
{
    sfSocketStatus status = sfSocketDone;

    for (int i = 0; i < NET_MAX_READS && status == sfSocketDone; i++) {
        status = sfTcpSocket_receivePacket(net->peers[id].sock, net->in);
        if (status == sfSocketDone)
            handle_msg(net, world, id);
    }
    if (status == sfSocketDisconnected || status == sfSocketError) {
        peer_close(&net->peers[id]);
        world->players[id].used = false;
    }
}

static void broadcast(net_t *net, const world_t *world)
{
    peer_t *peer = NULL;

    for (int id = 1; id < MAX_PLAYERS; id++) {
        peer = &net->peers[id];
        if (peer_flush(peer)) {
            packet_write_state(peer->out, world, id);
            peer_send(peer);
        }
    }
}

void net_host_update(net_t *net, world_t *world, float dt)
{
    accept_peer(net, world);
    for (int id = 1; id < MAX_PLAYERS; id++) {
        if (net->peers[id].sock != NULL)
            receive_peer(net, world, id);
    }
    net->tick += dt;
    if (net->tick < NET_TICK)
        return;
    net->tick = 0.0f;
    broadcast(net, world);
}
