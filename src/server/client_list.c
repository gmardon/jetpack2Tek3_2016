#include "server.h"

int		add_client(t_server *server, t_client *client)
{
    t_clist	*tmp;
    t_clist	*new;

    tmp = server->client_list;
    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    new = my_malloc(sizeof(t_clist));
    new->client = client;
    new->next = NULL;
    if (tmp == NULL)
        server->client_list = new;
    else
        tmp->next = new;
    return (0);
}

int	remove_client(t_server *server, int fd)
{
  t_clist	*tmp;
  t_clist	*old;

  tmp = server->client_list;
  old = NULL;
  while (tmp != NULL)
    {
      if (tmp->client->fd == fd)
	break;
      old = tmp;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    return (0);
  if (old == NULL)
    server->client_list = tmp->next;
  else
    old->next = tmp->next;
  free(tmp->client);
  free(tmp);
  return (1);
}

int	clients_length(t_clist *client_list)
{
  t_clist	*tmp;
  int		i;

  i = 0;
  tmp = client_list;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      i++;
    }
  return (i);
}

t_client *get_client_from_id(t_server *server, int id)
{
  t_clist	*tmp;
  t_client	*ret;

  ret = NULL;
  tmp = server->client_list;
  while (tmp != NULL)
    {
      if (tmp->client->id == id)
        {
            ret = tmp->client;
            break;
        }
      tmp = tmp->next;
    }
  return (ret);
}