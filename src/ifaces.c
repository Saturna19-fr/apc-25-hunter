/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** ifaces.c : liste des interfaces reseau IPv4 de la machine
*/

#include "net.h"

#include <ifaddrs.h>
#include <net/if.h>
#include <netinet/in.h>

static void copy_text(char *dest, const char *src)
{
    int i = 0;

    for (; i < IFACE_LEN - 1 && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
}

/*
** Tailscale attribue des adresses dans la plage 100.64.0.0/10.
*/
static void fill_iface(iface_t *iface, const struct ifaddrs *item)
{
    const struct sockaddr_in *in = (const struct sockaddr_in *)item->ifa_addr;
    const uint8_t *bytes = (const uint8_t *)&in->sin_addr.s_addr;
    sfIpAddress ip =
        sfIpAddress_fromBytes(bytes[0], bytes[1], bytes[2], bytes[3]);
    bool tailscale = bytes[0] == CGNAT_FIRST && bytes[1] >= CGNAT_MIN
        && bytes[1] <= CGNAT_MAX;

    copy_text(iface->name, tailscale ? "Tailscale" : item->ifa_name);
    copy_text(iface->address, ip.address);
}

static bool is_usable(const struct ifaddrs *item)
{
    if (item->ifa_addr == NULL || item->ifa_addr->sa_family != AF_INET)
        return false;
    return (item->ifa_flags & IFF_UP) != 0;
}

int ifaces_list(iface_t *list, int max)
{
    struct ifaddrs *all = NULL;
    int count = 1;

    copy_text(list[0].name, "Toutes");
    copy_text(list[0].address, IFACE_ALL);
    if (getifaddrs(&all) != 0)
        return count;
    for (struct ifaddrs *item = all; item != NULL && count < max;
        item = item->ifa_next) {
        if (is_usable(item)) {
            fill_iface(&list[count], item);
            count++;
        }
    }
    freeifaddrs(all);
    return count;
}
