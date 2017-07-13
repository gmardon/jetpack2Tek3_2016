#include "server.h"

t_server	*create_server(t_configuration *config)
{
  t_server	*server;

  server = get_server_socket(config->port);
  //server->client_list = NULL;
  server->configuration = config;
  server->max_id = 1;
  server->gamemap = init_map(config->map);
  FD_ZERO(&server->master);
  FD_SET(server->fd, &server->master);
  return (server);
}

void	handle_io(t_client *client, t_server *server)
{
  char	*buffer;
  int	rc;

  buffer = my_malloc(BUFFER_SIZE);
  memset(buffer, 0, BUFFER_SIZE);
  rc = recv(client->fd, buffer, BUFFER_SIZE, 0);
  if (rc < 0)
    {
      if (errno != EWOULDBLOCK)
	close_client(client, server);
      return;
    }
  if (rc == 0)
    {
      close_client(client, server);
      return;
    }
  if (buffer[rc - 1] == '\n')
    buffer[rc - 1] = 0;
  printf("< %s\n", buffer);
  handle_client_message(buffer, client, server);
}

void		handle_new_client(t_server *server, int *max)
{
    t_client	*client;

    client = accept_client(server);
    FD_SET(client->fd, &server->master);
    if (client->fd > *max)
        *max = client->fd;

    if (clients_length(server->client_list) >= 2)
        {
            send_message(client, "MAX USER REACHED\n");
            close_client(client, server);
            return;
        }
    else
        add_client(server, client);
    printf("New client connected from <%s:%d>\n",
        get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}

void start_server(t_server *server)
{
  int			max;
  fd_set		read_fds;
  t_clist		*tmp;

  max = server->fd;
  printf("start on port %d, waiting for connections...\n", server->configuration->port);
  while (TRUE)
    {
      read_fds = server->master;
      if (select(max + 1, &read_fds, NULL, NULL, NULL) == -1)
	    my_error("select", -1);
      if (FD_ISSET(server->fd, &read_fds))
	    handle_new_client(server, &max);
      tmp = server->client_list;
      while (tmp != NULL)
        {
            if (FD_ISSET(tmp->client->fd, &read_fds))
                handle_io(tmp->client, server);
            tmp = tmp->next;
        }
    }
}