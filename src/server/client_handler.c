/*
** client_handler.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 22:42:44 2017 Aurelien
** Last update Sun Jul  2 22:43:19 2017 Aurelien
*/
#include "server.h"

static t_cmd g_cmd_tab[] =
  {
    {"ID", &handle_id},
    {"", 0}
  };

void handle_client_message(char *buffer, t_client *client, t_server *server)
{
  int index;
  char **message;

  message = strsplit(buffer, " ");
  index = 0;
  while (g_cmd_tab[index].handler)
    {
      if (strncmp(g_cmd_tab[index].cmd, message[0], strlen(message[0])) == 0) 
      {
        (g_cmd_tab[index].handler)(buffer, client, server);
      }
      index++;
    }
}
