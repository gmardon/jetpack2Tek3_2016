#ifndef _JETPACK2TEK3_H_
#define _JETPACK2TEK3_H_
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void my_error(char *msg, int exit_code);
void *my_malloc(int size);
void set_non_blocking(int socket);
char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);
#endif