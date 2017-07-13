#ifndef _SERVER_H_
#define _SERVER_H_
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 2048
#include "jetpack.h"

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

typedef struct		s_clist
{
    t_client		*client;
    struct s_clist	*next;
}			t_clist;

typedef struct s_server
{
    int			fd;
    struct sockaddr_in	in;
    int			max_id;
    fd_set		master;
    t_clist		*client_list;
    t_configuration	*configuration;
    t_gamemap         *gamemap;
}			    t_server;

t_client *accept_client(t_server *server);
t_server *get_server_socket(int port);
t_server *create_server(t_configuration *config);
t_configuration	*parse_args(int argc, char *argv[]);
void start_server(t_server *server);
#endif