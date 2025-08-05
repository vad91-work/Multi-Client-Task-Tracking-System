
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

#include "database.h"

#define LOCAL_HOST "127.0.0.1"
#define PORT 4444
#define OP_LEN 15
#define MAX_CONN 500
#define PROTOCOL_HEADER_LEN 10


//user data
struct user_s{
    char username[50];
    char password[60];
    char token[50];
};

//user structure type
typedef struct user_s user_t;

user_t logged_users[MAX_CONN];

void *client_func(void *arg);
int register_user(int client_sock);
int get_user_and_password(int client_sock, user_t *user);
int login_user(int client_sock);

#endif