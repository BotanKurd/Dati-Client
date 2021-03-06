//
// Created by Botan on 27/10/18.
//


#include <malloc.h>
#include <buffer.h>
#include <shell.h>
#include <netinet/in.h>
#include <variable.h>

#include "buffer.h"

void writeByte(char byte, int socket) {
    send(socket, &byte, 1, 0);
}

void writeUByte(unsigned char byte, int socket) {
    send(socket, &byte, 1, 0);
}


void writeShort(int16_t short_value, int socket) {
    char buffer[2];
    memcpy(buffer, &short_value, 2);
    send(socket, buffer, 2, 0);
}


void writeUShort(__uint16_t u16, int socket) {
    char buffer[2];
    memcpy(buffer, &u16, 2);
    send(socket, buffer, 2, 0);
}

void writeString(char *str, int socket) {
    send(socket, str, strlen(str), 0);
}

void writeInt(int32_t value, int socket) {
    char buffer[4];

    memcpy(buffer, &value, 4);

    send(socket, buffer, 4, 0);
}

void writeUInt(__uint32_t value, int socket) {
    unsigned char buffer[4];

    memcpy(buffer, &value, 4);

    send(socket, buffer, 4, 0);
}

void writeLong(int64_t value, int socket) {
    char buffer[8];

    memcpy(buffer, &value, 8);

    send(socket, buffer, 8, 0);
}

void writeULong(__uint64_t value, int socket) {
    unsigned char buffer[8];

    memcpy(buffer, &value, 8);

    send(socket, buffer, 8, 0);
}

char *readString(size_t size, int socket) {
    char *buffer = malloc(size + 1);
    ssize_t readSize = recv(socket, buffer, size, 0);

    if (readSize < 0)
        onDisconnect();


    buffer[size] = '\0';
    return buffer;
}

__uint16_t readUShort(int socket) {
    unsigned char buffer[2];
    ssize_t readSize = recv(socket, buffer, 2, 0);
    if (readSize < 0)
        onDisconnect();
    return (__uint16_t) buffer[0] | ((__uint16_t) buffer[1] << 8);
}

unsigned char readUByte(int socket) {
    unsigned char buffer;
    ssize_t readSize = recv(socket, &buffer, 1, 0);
    if (readSize < 0)
        onDisconnect();
    return buffer;
}

__uint32_t readUInt(int socket) {
    unsigned char buffer[4];
    ssize_t readSize = recv(socket, buffer, 4, 0);

    if (readSize < 0)
        onDisconnect();

    __uint32_t value = 0;

    memcpy(&value, buffer, 4);

    return value;
}

__uint64_t readULong(int socket) {
    unsigned char buffer[8];
    ssize_t readSize = recv(socket, buffer, 8, 0);

    if (readSize < 0)
        onDisconnect();

    __uint64_t value = 0;

    memcpy(&value, buffer, 8);

    return value;
}

Node *valueChar(char c, char *key) {
    Node *value = malloc(sizeof(value));

    value->key = key;
    value->value = (void *) c;
    value->type = CHAR;

    return value;
}

Node *valueUChar(unsigned char c, char *key) {
    Node *value = malloc(sizeof(value));

    value->key = key;
    value->value = (void *) c;
    value->type = UCHAR;

    return value;
}

Node *valueShort(int16_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = SHORT;

    return node;
}

Node *valueUShort(uint16_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = USHORT;

    return node;
}

Node *valueLong(int64_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = LONG;

    return node;
}

Node *valueULong(uint64_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = ULONG;

    return node;
}

Node *valueInt(int32_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = INT;

    return node;
}

Node *valueUInt(uint32_t value, char *key) {
    Node *node = malloc(sizeof(node));

    node->key = key;
    node->value = (void *) value;
    node->type = UINT;

    return node;
}

Node *valueString(char *s, char *key) {
    Node *value = malloc(sizeof(value));

    value->key = key;
    value->value = (void *) s;
    value->type = STRING;

    return value;
}


void serializeValue(Node *value, int socket) {
    if (strlen(value->key) > 255)
        return;

    writeUByte((unsigned char) strlen(value->key), socket);

    writeString(value->key, socket);

    writeUByte(value->type, socket);

    if (value->type == STRING) {
        writeUInt((uint32_t) strlen((const char *) value->value), socket);
    }

    if (value->type != FLOAT && value->type != DOUBLE)
        VAR_WRITER[value->type](value->value, socket);
}


int16_t getShort(const char *buffer) {
    int16_t value = 0;

    memcpy(&value, buffer, 2);

    return value;
}

__uint16_t getUShort(const char *buffer) {
    __uint16_t value = 0;

    memcpy(&value, buffer, 2);

    return value;
}

__uint32_t getUInt(const char *buffer) {
    __uint32_t value = 0;

    memcpy(&value, buffer, 4);

    return value;
}

int32_t getInt(const char *buffer) {
    int32_t value = 0;

    memcpy(&value, buffer, 4);

    return value;
}

__uint64_t getULong(const char *buffer) {
    __uint64_t value = 0;

    memcpy(&value, buffer, 8);

    return value;
}

int64_t getLong(const char *buffer) {
    int64_t value = 0;

    memcpy(&value, buffer, 8);

    return value;
}

void onDisconnect() {
    setColor(RED);
    println("Disconnected from server");
}
