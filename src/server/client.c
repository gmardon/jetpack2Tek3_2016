#include "server.h"

void send_message(t_client *client, char *msg, ...)
{
  char		*content;
  int		len;
  va_list	args;

  content = my_malloc(40960);
  if (client->fd)
    {
      va_start(args, msg);
      len = vsprintf(content, strdup(msg), args);
      printf("> %s", content);
      write(client->fd, content, len);
      va_end(args);
    }
}

void close_client(t_client *client, t_server *server)
{
  if (client->fd > 0)
    {
      FD_CLR(client->fd, &server->master);
      close(client->fd);
    }
  client->fd = 0;
  printf("Client disconnected <%s:%d>\n", 
        get_client_addr(client->in), get_client_port(client->in));
}

t_client *create_client(int socket, struct sockaddr_in in, t_server *server)
{
  t_client *client;

  client = my_malloc(sizeof(t_client));
  client->fd = socket;
  set_non_blocking(client->fd);
  client->in = in;
  client->id = server->max_id++;
  return (client);
}