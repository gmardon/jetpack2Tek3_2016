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
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 2048

void my_error(char *msg, int exit_code);
void *my_malloc(int size);
char *get_client_addr(struct sockaddr_in client);
int get_client_port(struct sockaddr_in client);
char **strsplit(const char* str, const char* delim);
char *get_next_line(const int fd);
#endif