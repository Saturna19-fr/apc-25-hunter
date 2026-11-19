/*
** EPITECH PROJECT, 2026
** G-MUL-100-PAR-1-1-myhunter-40
** File description:
** protocol.h : messages echanges entre l'hote et les clients
*/

#ifndef PROTOCOL_H_
    #define PROTOCOL_H_
    #include <CSFML/Network.h>
    #include "world.h"

/*
** Client -> hote :
**   MSG_HELLO  : pseudo (NAME_LEN octets)
**   MSG_CURSOR : x, y (float)
**   MSG_SHOOT  : x, y (float)
** Hote -> client :
**   MSG_STATE  : id du client, phase, temps restant, joueurs, canards
*/
typedef enum msg_e {
    MSG_HELLO = 1,
    MSG_CURSOR,
    MSG_SHOOT,
    MSG_STATE
} msg_t;

void packet_write_hello(sfPacket *packet, const char *name);
void packet_write_input(sfPacket *packet, uint8_t type, float x, float y);
void packet_read_name(sfPacket *packet, char *name);
void packet_write_state(sfPacket *packet, const world_t *world, int id);
bool packet_read_state(sfPacket *packet, world_t *world, int *id);

#endif /* !PROTOCOL_H_ */
