
#ifndef SERVER_H
#define SERVER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <pthread.h>

#define LOCAL_HOST "127.0.0.1"
#define PORT 4444
#define OP_LEN 15
#define MAX_CONN 500
#define PROTOCOL_HEADER_LEN 10

void *client_func(void *arg);

#endif