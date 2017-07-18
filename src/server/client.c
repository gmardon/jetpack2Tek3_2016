#include "server.h"

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

void close_client(t_client *client, t_server *server)
{
  if (client->fd > 0)
    {
      FD_CLR(client->fd, &server->master);
      close(client->fd);
      remove_client(server, client->fd);
    }
  printf("Client disconnected <%s:%d>\n", 
        get_client_addr(client->in), get_client_port(client->in));
}

void update_position(t_client *client, t_server *server)
{
  double	y;
  double	vel;
  double	diff;
  t_clist *tmp;

  diff = (double) 5 * (double)25000;
  diff /= (double) 400000;
  client->velocity += server->configuration->gravity * -1 * (double)(client->jetpack * 2 - 1)
    * (double)25000 / (double) 1000000;
  y = client->y;
  y += client->velocity * (double) 25000 / (double)1000000;
  vel = 0;
  if (y < 0)
    y = 0;
  else if (y > server->gamemap->height - 1)
    y = server->gamemap->height - 1;
  else
    vel = client->velocity;
  client->velocity = vel;
  client->y = y;
  client->x += diff;
  tmp = server->client_list;
  while (tmp != NULL && tmp->client != NULL)
  {
    send_message(tmp->client, "PLAYER %d %f %f %d\n", client->id, client->x, client->y, client->score);
    tmp = tmp->next;
  }  
}

t_client *create_client(int socket, struct sockaddr_in in, t_server *server)
{
  t_client *client;

  client = my_malloc(sizeof(t_client));
  client->fd = socket;
  set_non_blocking(client->fd);
  client->in = in;
  client->id = server->max_id++;
  client->state = CLIENT_STATE_CONNECTED;
  client->jetpack = 0;
  client->x = 0;
  client->y = server->gamemap->height / 2;
  client->dead = 0;
  return (client);
}