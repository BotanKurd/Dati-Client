//
// Created by Botan on 27/10/18.
//

#ifndef DATI_CLIENT_H
#define DATI_CLIENT_H

#include <stdint.h>

struct session {
    unsigned char connected;
    int socket;
} session;

struct client {
    struct session session;
    char *host;
    uint16_t port;

    char *username;
    char *password;

};

unsigned char begin_connection(struct client client);

#endif //DATI_CLIENT_H