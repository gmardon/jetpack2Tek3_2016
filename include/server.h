#ifndef _SERVER_H_
#define _SERVER_H_
#include "jetpack.h"
typedef struct		s_server
{
  int			fd;
  struct sockaddr_in	in;
  int			max_id;
  fd_set		master;
  t_configuration	*configuration;
}			t_server;

t_client *accept_client(t_server *server);
t_server *get_server_socket(int port);
t_server *create_server(t_configuration *config);
#endif