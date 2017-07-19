/*
** client.c for client in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:57:08 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:57:14 2017 nathan.bonnet@epitech.eu
*/

#include "client.h"

void send_message(t_client *client, char *msg, ...)
{
  char		*content;
  int		len;
  va_list	args;

  content = my_malloc(BUFFER_SIZE);
  if (client->fd)
    {
      va_start(args, msg);
      len = vsprintf(content, strdup(msg), args);
      printf("> %s", content);
      write(client->fd, content, len);
      va_end(args);
    }
}

void close_client(t_client *client)
{
  if (client->fd > 0)
    {
      close(client->fd);
    }
  printf("Client disconnected <%s:%d>\n",
        get_client_addr(client->in), get_client_port(client->in));
}

t_client	*create_client(t_configuration *config)
{
  t_client	*client;

  client = my_malloc(sizeof(t_client));
  client->id = 0;
  client->configuration = config;
  return (client);
}

void start_client(t_client *client)
{
    connect_client(client);
    send_message(client, "ID\n");
    makeWindow(client);
}
