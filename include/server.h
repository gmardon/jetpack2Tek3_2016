#ifndef _SERVER_H_
#define _SERVER_H_
#define TRUE 1
#define FALSE 0
#include "jetpack.h"
#define CLIENT_STATE_UNDEFINED 0
#define CLIENT_STATE_CONNECTED 1
#define CLIENT_STATE_READY 2
#define SERVER_STATE_WAITING 1
#define SERVER_STATE_STARTED 2

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
    int             state;
    int             score;
    double          x;
    double          y;
    int             jetpack;
    double		    velocity;
    char            dead;
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
    int state;
}			    t_server;

typedef void (*cmd_function)(char* buffer, t_client *client, t_server *server);

typedef struct	s_cmd
{
  char		*cmd;
  cmd_function	handler;
}		t_cmd;

t_client *accept_client(t_server *server);
t_server *get_server_socket(int port);
t_server *create_server(t_configuration *config);
t_configuration	*parse_args(int argc, char *argv[]);
void start_server(t_server *server);
int	add_client(t_server *server, t_client *client);
int	remove_client(t_server *server, int fd);
int	clients_length(t_clist *client_list);
void send_message(t_client *client, char *msg, ...);
void close_client(t_client *client, t_server *server);
t_client *create_client(int socket, struct sockaddr_in in, t_server *server);
void check_near_objects(t_client *client, t_server *server);
t_gamemap *init_map(char *filepath);
void handle_client_message(char *buffer, t_client *client, t_server *server);
void update_position(t_client *client, t_server *server);

// HANDLERS //
void handle_id(char *cmd, t_client *client, t_server *server);
void handle_ready(char *cmd, t_client *client, t_server *server);
void handle_map(char *cmd, t_client *client, t_server *server);
void handle_fire(char *cmd, t_client *client, t_server *server);
#endif