#include "server.h"

t_server	*create_server(t_configuration *config)
{
  t_server	*server;

  server = get_server_socket(config->port);
  server->client_list = NULL;
  server->configuration = config;
  server->max_id = 1;
  server->gamemap = init_map(config->map);
  server->state = SERVER_STATE_WAITING;
  server->winner = NULL;
  FD_ZERO(&server->master);
  FD_SET(server->fd, &server->master);
  return (server);
}

void	handle_io(t_client *client, t_server *server)
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
  messages = strsplit(buffer, "\n");
  index = 0;
  while (messages[index])
    {
        printf("< %s\n", messages[index]);
        handle_client_message(messages[index], client, server);
        index++;
    }
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
}


void game_tick(t_server *server)
{    
    t_clist		*tmp;

    if (server->state == SERVER_STATE_WAITING)
        return;
    if (clients_alive_length(server->client_list) == 1 || server->state == SERVER_STATE_FINISHED)
    {           
        if (server->winner == NULL && clients_alive_length(server->client_list) == 1)
            server->winner = server->client_list->client;

        tmp = server->client_list;
        while (tmp != NULL && tmp->client != NULL)
        {
            if (server->winner)
                send_message(tmp->client, "FINISH %i\n", server->winner->id);
            else
                send_message(tmp->client, "FINISH -1\n");
            close_client(tmp->client, server);
            tmp = tmp->next;
        }
        return;
    }
    tmp = server->client_list;
    while (tmp != NULL && tmp->client != NULL)
    {
        check_position(tmp->client, server);
        update_position(tmp->client, server);
        check_near_object(tmp->client, server);
        tmp = tmp->next;
    }
}

void start_server(t_server *server)
{
    int			max;
    fd_set		read_fds;
    t_clist		*tmp;
    int milliseconds = 50;

    max = server->fd;
    printf("start on port %d, waiting for connections...\n", server->configuration->port);
    while (TRUE)
    {
        struct timeval tv;
        tv.tv_sec = milliseconds / 1000;
        tv.tv_usec = (milliseconds % 1000) * 1000;
        read_fds = server->master;
        if (select(max + 1, &read_fds, NULL, NULL, &tv) == -1)
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
        game_tick(server);
    }
}