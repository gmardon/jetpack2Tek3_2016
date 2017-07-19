/*
** network.c for network in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by Nathan
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 10:13:52 2017 Nathan
** Last update Wed Jul 19 10:56:43 2017 Nathan
*/

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int socket_connect(const char *ip, const char *port_str)
{
    struct protoent *pe;
    int fd;
    struct sockaddr_in s_in;
    int port;
    port = atoi(port_str);
    pe = getprotobyname("TCP");
    if (!pe)
        return 1;
    fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (fd == -1)
        return 1;
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = inet_addr((strcmp(ip, "localhost") == 0 ? "127.0.0.1" : ip));
    if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
        if (close(fd) == -1)
            return 1;
        return 1;
    }
  	printf("%s\n", "OKAY");
    return fd;
}
