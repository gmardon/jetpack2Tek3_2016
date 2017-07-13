#ifndef _JETPACK2TEK3_H_
#define _JETPACK2TEK3_H_
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void my_error(char *msg, int exit_code);
void *my_malloc(int size);
void set_non_blocking(int socket);
#endif