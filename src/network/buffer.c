//
// Created by Botan on 27/10/18.
//


#include <malloc.h>
#include <decimal.h>
#include <variable.h>
#include <sys/socket.h>
#include <buffer.h>
#include <shell.h>
#include <netinet/in.h>

#include "buffer.h"

void write_byte(char byte, int socket) {
    send(socket, &byte, 1, 0);
}

void write_ubyte(unsigned char byte, int socket) {
    send(socket, &byte, 1, 0);
}


void write_short(int16_t short_value, int socket) {
    char buffer[2];

    buffer[0] = (char) (short_value >> 8);
    buffer[1] = (char) (short_value);

    send(socket, buffer, 2, 0);
}


void write_ushort(__uint16_t u16, int socket) {
    char buffer[2];
    buffer[0] = (char) (u16);
    buffer[1] = (char) ((u16 >> 8));
    send(socket, buffer, 2, 0);
}

void write_string(char *str, int socket) {
    send(socket, str, strlen(str), 0);
}

void write_int(int32_t value, int socket) {
    char buffer[4];

    for (int i = 0; i < 4; i++)
        buffer[i] = (char) ((value >> (8 * i)));

    send(socket, buffer, 4, 0);
}

void write_uint(__uint32_t value, int socket) {
    unsigned char buffer[4];

    for (int i = 0; i < 4; i++)
        buffer[i] = (unsigned char) ((value >> (8 * i)));

    send(socket, buffer, 4, 0);
}

void write_long(int64_t value, int socket) {
    char buffer[8];

    for (int i = 0; i < 8; i++)
        buffer[i] = (char) ((value >> (8 * i)));

    send(socket, buffer, 8, 0);
}

void write_ulong(__uint64_t value, int socket) {
    unsigned char buffer[8];

    for (int i = 0; i < 8; i++)
        buffer[i] = (unsigned char) ((value >> (8 * i)));

    send(socket, buffer, 8, 0);
}


char *read_string(size_t size, int socket) {
    char *buffer = malloc(size + 1);
    recv(socket, buffer, size, 0);
    buffer[size] = '\0';
    return buffer;
}

__uint16_t read_ushort(int socket) {
    unsigned char buffer[2];
    recv(socket, buffer, 2, 0);
    return (__uint16_t) buffer[0] | ((__uint16_t) buffer[1] << 8);
}

unsigned char read_ubyte(int socket) {
    unsigned char buffer;
    recv(socket, &buffer, 1, 0);
    return buffer;
}

__uint64_t read_ulong(int socket) {
    unsigned char buffer[8];
    recv(socket, buffer, 8, 0);

    __uint64_t value = 0;

    for (int i = 0; i < 8; i++)
        value += (buffer[i] << (8 * i));

    return value;
}

value value_char(char c) {
    value value = {"", CHAR, (void *) c};
    return value;
}

value value_uchar(unsigned char c) {
    value value = {"", UCHAR, (void *) c};
    return value;
}

value value_short(int16_t i) {
    value value = {"", SHORT, (void *) i};
    return value;
}

value value_ushort(uint16_t i) {
    value value = {"", USHORT, (void *) i};
    return value;
}

value value_long(int64_t i) {
    value value = {"", LONG, (void *) i};
    return value;
}

value value_ulong(uint64_t i) {
    value value = {"", ULONG, (void *) i};
    return value;
}

value value_int(int32_t i) {
    value value = {"", INT, (void *) i};
    return value;
}

value value_uint(uint32_t i) {
    value value = {"", UINT, (void *) i};
    return value;
}

value value_float(float f) {
    char *buffer = malloc(4);
    write_float(f, buffer);

    value value = {"", DOUBLE, (void *) buffer};
    return value;
}

value value_double(double d) {
    char *buffer = malloc(8);
    write_double(d, buffer);

    value value = {"", DOUBLE, (void *) buffer};

    return value;
}

value value_string(char *s) {
    value value = {"", STRING, (void *) s};
    return value;
}


void serialize_value(value value, int socket) {
    if (strlen(value.key) > 255)
        return;

    write_ushort((unsigned char) strlen(value.key), socket);

    write_string(value.key, socket);

    write_ubyte(value.type, socket);

    if (value.type == STRING) {
        write_uint((uint32_t) strlen((const char *) value.value), socket);
    }

    switch (value.type) {
        case CHAR:
            write_byte((char) value.value, socket);
            break;

        case UCHAR:
            write_ubyte((unsigned char) value.value, socket);
            break;

        case SHORT:
            write_short((int16_t) value.value, socket);
            break;

        case USHORT:
            write_ushort((uint16_t) value.value, socket);
            break;

        case INT:
            write_int((int32_t) value.value, socket);
            break;

        case UINT:
            write_uint((uint32_t) value.value, socket);
            break;

        case LONG:
            write_long((int64_t) value.value, socket);
            break;

        case ULONG:
            write_ulong((uint64_t) value.value, socket);
            break;

        case FLOAT:
            write_string((char *) value.value, socket);
            break;

        case DOUBLE:
            println("Double : %s", (char *) value.value);
            write_string((char *) value.value, socket);
            break;

        case STRING:
            write_string((char *) value.value, socket);
            break;

    }

}
