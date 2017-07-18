#ifndef CLIENT_H
#define CLIENT_H

typedef struct		s_client
{
  int			fd;
  struct sockaddr_in	in;
  int			max_id;
  fd_set		master;
  t_configuration	*configuration;
}			t_client;

#endif
