#include "server.h"

static t_cmd g_cmd_tab[] =
  {
    {"ID", &handle_id},
    {"READY", &handle_ready},
    {"MAP", &handle_map},
    {"FIRE", &handle_fire},
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
        break;
      }
      index++;
    }
}
