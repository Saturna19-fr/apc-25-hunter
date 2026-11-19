/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** net_client.c : le client envoie ses actions et recoit l'etat du jeu
*/

#include "net.h"
#include "protocol.h"
#include "my.h"

static sfTcpSocket *open_socket(const char *host, unsigned short port)
{
    sfIpAddress address = sfIpAddress_fromString(host);
    sfTcpSocket *sock = NULL;

    if (my_strcmp(address.address, sfIpAddress_None.address) == 0)
        return NULL;
    sock = sfTcpSocket_create();
    if (sock == NULL)
        return NULL;
    if (sfTcpSocket_connect(sock, address, port, sfSeconds(NET_TIMEOUT))
        != sfSocketDone) {
        sfTcpSocket_destroy(sock);
        return NULL;
    }
    return sock;
}

bool net_client_start(net_t *net, const char *host, unsigned short port)
{
    sfTcpSocket *sock = open_socket(host, port);

    if (sock == NULL)
        return false;
    net->in = sfPacket_create();
    if (!peer_attach(&net->peers[0], sock) || net->in == NULL) {
        net_close(net);
        return false;
    }
    net->role = NET_CLIENT;
    net->my_id = -1;
    return true;
}

void net_client_hello(net_t *net, const char *name)
{
    peer_t *server = &net->peers[0];

    packet_write_hello(server->out, name);
    peer_send(server);
}

bool net_client_receive(net_t *net, world_t *world)
{
    peer_t *server = &net->peers[0];
    sfSocketStatus status = sfSocketDone;

    for (int i = 0; i < NET_MAX_READS && status == sfSocketDone; i++) {
        status = sfTcpSocket_receivePacket(server->sock, net->in);
        if (status == sfSocketDone && sfPacket_readUint8(net->in) == MSG_STATE)
            packet_read_state(net->in, world, &net->my_id);
    }
    return status != sfSocketDisconnected && status != sfSocketError;
}

void net_client_tick(net_t *net, const world_t *world, float dt)
{
    peer_t *server = &net->peers[0];
    const player_t *me = NULL;

    net->tick += dt;
    if (net->tick < NET_TICK || net->my_id < 0 || !peer_flush(server))
        return;
    net->tick = 0.0f;
    me = &world->players[net->my_id];
    packet_write_input(server->out, MSG_CURSOR, me->cx, me->cy);
    peer_send(server);
}

void net_client_shoot(net_t *net, float x, float y)
{
    peer_t *server = &net->peers[0];

    if (!peer_flush(server))
        return;
    packet_write_input(server->out, MSG_SHOOT, x, y);
    peer_send(server);
}
