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
#include "client.h"

void connect_client(t_client *client)
{
    struct protoent *pe;

    pe = getprotobyname("TCP");
    if (!pe)
        exit(84);
    client->fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (client->fd == -1)
        my_error("Cannot create socket!\n", 84);
    client->in.sin_family = AF_INET;
    client->in.sin_port = htons(client->configuration->port);
    client->in.sin_addr.s_addr = inet_addr((strcmp(client->configuration->host, "localhost") == 0 ? "127.0.0.1" : client->configuration->host));
    if (connect(client->fd, (struct sockaddr *)&client->in, sizeof(client->in)) == -1) {
        if (close(client->fd) == -1)
            my_error("Cannot connect!\n", 84);
        my_error("Cannot connect!\n", 84);
    }
}

void	handle_io(t_client *client)
{
  char	*buffer;
  int	rc;
  char **messages;
  int index;

  buffer = my_malloc(BUFFER_SIZE);
  memset(buffer, 0, BUFFER_SIZE);
  rc = recv(client->fd, buffer, BUFFER_SIZE, 0);
  if (rc < 0)
    {
      if (errno != EWOULDBLOCK)
	    close_client(client);
      return;
    }
  if (rc == 0)
    {
      close_client(client);
      return;
    }
  if (buffer[rc - 1] == '\n')
    buffer[rc - 1] = 0;
  messages = strsplit(buffer, "\n");
  index = 0;
  while (messages[index])
    {
        printf("< %s\n", messages[index]);
        handle_message(messages[index], client);
        index++;
    }
  }