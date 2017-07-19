/*
** main.c for main in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:41:56 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:41:59 2017 nathan.bonnet@epitech.eu
*/

#include "client.h"

int main(int argc, char *argv[])
{
    t_configuration	*config;
    t_client *client;
    config = parse_args(argc, argv);
    client = create_client(config);
    start_client(client);
    return (0);
}
