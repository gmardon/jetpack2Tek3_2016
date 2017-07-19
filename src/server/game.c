/*
** game.c for game in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:33:08 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:33:10 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

t_client	*get_winner(t_server *server)
{
  t_clist	*tmp;
  int		best_score;
  t_client	*best_player;

  tmp = server->client_list;
  best_player = NULL;
  best_score = 0;
  while (tmp != NULL && tmp->client != NULL)
    {
      if (tmp->client->dead == 1)
        {
	  tmp = server->client_list;
	  while (tmp != NULL && tmp->client != NULL)
            {
	      if (tmp->client->dead == 0)
		return (tmp->client);
	      tmp = tmp->next;
            }
        }
      else if (best_score < tmp->client->score)
        {
	  best_player = tmp->client;
	  best_score = tmp->client->score;
        }
      tmp = tmp->next;
    }
  return (best_player);
}

void		check_near_object(t_client *client, t_server *server)
{
  t_clist	*tmp;
  char		cell;
  int		x;
  int		y;

  x = client->x;
  y = client->y;
  if (x > server->gamemap->width || y > server->gamemap->height)
    return;
  cell = server->gamemap->cells[y][x];
  if (cell == 'c')
    {
      client->score++;
      server->gamemap->cells[y][x] = 'o';
      tmp = server->client_list;
      while (tmp != NULL && tmp->client != NULL)
        {
	  send_message(tmp->client, "COIN %i %i %i\n", client->id, x, y);
	  tmp = tmp->next;
        }
    }
  else if (cell == 'e' && x == client->x && y == client->y)
    {
      tmp = server->client_list;
      client->dead = 1;
      if (server->winner == NULL)
	server->winner = get_winner(server);
      server->state = SERVER_STATE_FINISHED;
    }
}

void	check_position(t_client *client, t_server *server)
{
  if (client->x > server->gamemap->width && server->winner == NULL)
    {
      server->winner = get_winner(server);
      server->state = SERVER_STATE_FINISHED;
    }
}
