/*
** network.c for network in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by Nathan
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 10:13:52 2017 Nathan
** Last update Wed Jul 19 14:49:47 2017 Nathan
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
#include <unistd.h>
#include <fcntl.h>
#include "server.h"
#include "client.h"


t_client socket_connect(const char *ip, const char *port_str)
{
  	t_client client;
    struct protoent *pe;
    int port;
    port = atoi(port_str);
    pe = getprotobyname("TCP");
    if (!pe)
        exit(84);
    client.fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (client.fd == -1)
    exit(84);
    client.in.sin_family = AF_INET;
    client.in.sin_port = htons(port);
    client.in.sin_addr.s_addr = inet_addr((strcmp(ip, "localhost") == 0 ? "127.0.0.1" : ip));
    if (connect(client.fd, (struct sockaddr *)&client.in, sizeof(client.in)) == -1) {
        if (close(client.fd) == -1)
        	exit(84);
        exit(84);
    }
  	printf("%s\n", "OKAY");
    return client;
}

int main(int ac, char **av)
{
  if(ac == 3)
  {
      socket_connect(av[1], av[2]);
      makeWindow();
  }
}
