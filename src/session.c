/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** session.c : heberger, rejoindre ou quitter une partie
*/

#include "game.h"
#include "my.h"

#include <string.h>

static void reset_world(app_t *app)
{
    memset(&app->world, 0, sizeof(world_t));
    if (app->name[0] == '\0')
        str_copy(app->name, DEFAULT_NAME, NAME_LEN);
}

bool session_bind(app_t *app, const char *address)
{
    app->iface_count = ifaces_list(app->ifaces, MAX_IFACES);
    for (int i = 0; i < app->iface_count; i++) {
        if (my_strcmp(app->ifaces[i].address, address) == 0) {
            app->iface = i;
            return true;
        }
    }
    app->status = "Aucune interface réseau n'a cette adresse";
    return false;
}

void session_host(app_t *app)
{
    const char *address = app->ifaces[app->iface].address;
    bool started = false;

    reset_world(app);
    for (int i = 0; i < NET_PORT_TRIES && !started; i++)
        started =
            net_host_start(&app->net, (unsigned short)(NET_PORT + i), address);
    if (!started) {
        app->status = "Impossible d'écouter sur cette interface";
        return;
    }
    app->world.players[0].used = true;
    str_copy(app->world.players[0].name, app->name, NAME_LEN);
    app->status = NULL;
}

static unsigned short split_host(const char *src, char *host)
{
    int port = NET_PORT;
    int i = 0;

    for (; src[i] != '\0' && src[i] != ':'; i++)
        host[i] = src[i];
    host[i] = '\0';
    if (src[i] == ':')
        port = str_to_nb(&src[i + 1]);
    if (port <= 0)
        port = NET_PORT;
    return (unsigned short)port;
}

void session_join(app_t *app)
{
    char host[HOST_LEN];
    unsigned short port = split_host(app->host, host);

    reset_world(app);
    if (!net_client_start(&app->net, host, port)) {
        app->status = "Connexion impossible : vérifie l'adresse de l'hôte";
        return;
    }
    net_client_hello(&app->net, app->name);
    app->status = NULL;
}

void session_leave(app_t *app, const char *status)
{
    net_close(&app->net);
    memset(&app->world, 0, sizeof(world_t));
    app->status = status;
}
