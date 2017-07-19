/*
** server_socket.c for server_socket in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:17:06 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:21:39 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

t_client		*accept_client(t_server *server)
{
  t_client		*client;
  socklen_t		length;
  int			socket;
  struct sockaddr_in	in;

  length = sizeof(in);
  client = NULL;
  if ((socket = accept(server->fd, (struct sockaddr *)&in, &length)) == -1)
    my_error("Can't accept one client connection", -1);
  else
    client = create_client(socket, in, server);
  return (client);
}

t_server	*get_server_socket(int port)
{
  t_server	*server;
  int		opt;

  opt = TRUE;
  server = (t_server *)my_malloc(sizeof(struct s_server));
  if ((server->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    my_error("Can't create socket", -1);
  server->in.sin_family = AF_INET;
  server->in.sin_addr.s_addr = INADDR_ANY;
  server->in.sin_port = htons(port);
  bzero(&(server->in.sin_zero), 8);
  if ((setsockopt(server->fd, SOL_SOCKET, SO_REUSEADDR,
    (char *)&opt, sizeof(opt))) < 0)
    my_error("Can't allow multiple connection on socket", -1);
  if ((bind(server->fd, (struct sockaddr *)&server->in,
	    sizeof(server->in))) < 0)
    my_error("Can't bind socket", -1);
  if ((listen(server->fd, 10)) == -1)
    my_error("Can't listen the socket", -1);
  return (server);
}
