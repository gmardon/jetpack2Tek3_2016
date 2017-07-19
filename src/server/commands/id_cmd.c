/*
** id_cmd.c for id_cmd in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/commands/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:40:35 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:40:45 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

void handle_id(char *cmd, t_client *client, t_server *server)
{

    (void) server;
    (void) cmd;
    send_message(client, "ID %i\n", client->id);
}
