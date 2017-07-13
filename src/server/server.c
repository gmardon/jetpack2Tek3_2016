#include "server.h"


t_server	*create_server(t_configuration *config)
{
  t_server	*server;
  int		i;

  i = -1;
  server = get_server_socket(config->port);
  //server->client_list = NULL;
  server->configuration = config;
  server->max_id = 1;
  FD_ZERO(&server->master);
  FD_SET(server->fd, &server->master);
  return (server);
}