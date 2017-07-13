#ifndef _SERVER_H_
#define _SERVER_H_
typedef struct		s_server
{
  int			fd;
  struct sockaddr_in	in;
  int			max_id;
  fd_set		master;
  t_configuration	*configuration;
}			t_server;
#endif