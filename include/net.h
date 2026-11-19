/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** net.h : sockets TCP (module Network de la CSFML)
*/

#ifndef NET_H_
    #define NET_H_
    #include <CSFML/Network.h>
    #include "world.h"

    #define NET_PORT 4242
    #define NET_PORT_TRIES 10
    #define NET_PORT_MAX 65535
    #define NET_TICK 0.033f
    #define NET_TIMEOUT 3.0f
    #define NET_MAX_READS 64
    #define MAX_IFACES 12
    #define IFACE_LEN 16
    #define IFACE_ALL "0.0.0.0"
    #define CGNAT_FIRST 100
    #define CGNAT_MIN 64
    #define CGNAT_MAX 127

typedef enum net_role_e {
    NET_NONE,
    NET_HOST,
    NET_CLIENT
} net_role_t;

typedef struct iface_s {
    char name[IFACE_LEN];
    char address[IFACE_LEN];
} iface_t;

typedef struct peer_s {
    sfTcpSocket *sock;
    sfPacket *out;
    bool pending;
} peer_t;

typedef struct net_s {
    net_role_t role;
    sfTcpListener *listener;
    peer_t peers[MAX_PLAYERS];
    sfPacket *in;
    sfIpAddress local;
    unsigned short port;
    float tick;
    int my_id;
} net_t;

bool peer_attach(peer_t *peer, sfTcpSocket *sock);
void peer_close(peer_t *peer);
bool peer_flush(peer_t *peer);
void peer_send(peer_t *peer);
void net_close(net_t *net);

int ifaces_list(iface_t *list, int max);

bool net_host_start(net_t *net, unsigned short port, const char *address);
void net_host_update(net_t *net, world_t *world, float dt);

bool net_client_start(net_t *net, const char *host, unsigned short port);
void net_client_hello(net_t *net, const char *name);
bool net_client_receive(net_t *net, world_t *world);
void net_client_tick(net_t *net, const world_t *world, float dt);
void net_client_shoot(net_t *net, float x, float y);

#endif /* !NET_H_ */
