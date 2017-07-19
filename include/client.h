#ifndef CLIENT_H
#define CLIENT_H
#include "jetpack.h"
#include <netinet/in.h>
#include <SFML/Graphics.h>

typedef struct s_configuration
{
    int				port;
    char*		    host;
}				t_configuration;

typedef struct		s_client
{
  int			fd;
  struct sockaddr_in	in;
  int id;
  t_configuration	*configuration;
}			t_client;


typedef void (*cmd_function)(char* buffer, t_client *client);

typedef struct	s_cmd
{
  char		*cmd;
  cmd_function	handler;
}		t_cmd;


int makeWindow();
t_configuration	*parse_args(int argc, char *argv[]);
void handle_message(char *buffer, t_client *client);
t_client	*create_client(t_configuration *config);
void connect_client(t_client *client);
#endif
