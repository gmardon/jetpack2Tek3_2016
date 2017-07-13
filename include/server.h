#ifndef _SERVER_H_
#define _SERVER_H_
#define TRUE 1
#define FALSE 0
#include "jetpack.h"
#include <stdarg.h>
#include <unistd.h>

typedef struct s_gamemap
{
  int			height;
  int           width;
  char          **cells;
}			    t_gamemap;

typedef struct s_configuration
{
    int				port;
    int				gravity;
    char*		    map;
}				t_configuration;

typedef struct s_client
{
    int			fd;
    struct sockaddr_in	in;
    int             id;
}               t_client;

typedef struct s_server
{
  int			fd;
  struct sockaddr_in	in;
  int			max_id;
  fd_set		master;
  t_configuration	*configuration;
  t_gamemap         *gamemap;
}			    t_server;

t_client *accept_client(t_server *server);
t_server *get_server_socket(int port);
t_server *create_server(t_configuration *config);
t_configuration		*parse_args(int argc, char *argv[]);
#endif