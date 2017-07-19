/*
** main.c for main in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:56:11 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:56:20 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

int			main(int argc, char *argv[])
{
  t_configuration	*config;
  t_server		*server;
  config = parse_args(argc, argv);
  server = create_server(config);
  start_server(server);
  return (0);
}
