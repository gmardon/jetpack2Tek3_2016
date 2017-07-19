/*
** socket_utils.c for socket_utils in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:40:07 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:40:19 2017 nathan.bonnet@epitech.eu
*/


#include "jetpack.h"

char	*get_client_addr(struct sockaddr_in client)
{
  return (inet_ntoa(client.sin_addr));
}

int	get_client_port(struct sockaddr_in client)
{
  return (ntohs(client.sin_port));
}
