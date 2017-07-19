/*
** client_handler.c for client_handler in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:30:33 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:30:45 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

static	t_cmd g_cmd_tab[] =
  {
    {"ID", &handle_id},
    {"READY", &handle_ready},
    {"MAP", &handle_map},
    {"FIRE", &handle_fire},
    {"", 0}
  };

void	handle_client_message(char *buffer, t_client *client, t_server *server)
{
  int	index;
  char	**message;

  message = strsplit(buffer, " ");
  index = 0;
  while (g_cmd_tab[index].handler)
    {
      if (strncmp(g_cmd_tab[index].cmd, message[0], strlen(message[0])) == 0)
      {
        (g_cmd_tab[index].handler)(buffer, client, server);
        break;
      }
      index++;
    }
}
