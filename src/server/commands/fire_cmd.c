/*
** fire_cmd.c for fire_cmd in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/commands/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:39:59 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:40:13 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

void handle_fire(char *cmd, t_client *client, t_server *server)
{
    (void) server;
    (void) cmd;
    client->jetpack =! client->jetpack;
}
