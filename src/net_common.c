/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** net_common.c : envoi non bloquant et fermeture des sockets
*/

#include "net.h"

#include <string.h>

bool peer_attach(peer_t *peer, sfTcpSocket *sock)
{
    peer->sock = sock;
    peer->out = sfPacket_create();
    peer->pending = false;
    if (peer->sock == NULL || peer->out == NULL) {
        peer_close(peer);
        return false;
    }
    sfTcpSocket_setBlocking(sock, false);
    return true;
}

void peer_close(peer_t *peer)
{
    if (peer->sock != NULL)
        sfTcpSocket_destroy(peer->sock);
    if (peer->out != NULL)
        sfPacket_destroy(peer->out);
    peer->sock = NULL;
    peer->out = NULL;
    peer->pending = false;
}

/*
** Un envoi partiel doit etre repris avec le meme paquet : tant qu'il
** reste des octets en attente, on ne reecrit pas peer->out.
*/
void peer_send(peer_t *peer)
{
    sfSocketStatus status = sfTcpSocket_sendPacket(peer->sock, peer->out);

    if (status == sfSocketPartial)
        peer->pending = true;
    else if (status != sfSocketNotReady)
        peer->pending = false;
}

bool peer_flush(peer_t *peer)
{
    if (peer->sock == NULL)
        return false;
    if (peer->pending)
        peer_send(peer);
    return !peer->pending;
}

void net_close(net_t *net)
{
    for (int i = 0; i < MAX_PLAYERS; i++)
        peer_close(&net->peers[i]);
    if (net->listener != NULL)
        sfTcpListener_destroy(net->listener);
    if (net->in != NULL)
        sfPacket_destroy(net->in);
    memset(net, 0, sizeof(net_t));
}
