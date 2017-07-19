/*
** my_error.c for my_error in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:37:49 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:37:57 2017 nathan.bonnet@epitech.eu
*/

#include "jetpack.h"

void	my_error(char *msg, int exit_code)
{
  if (msg)
    printf("%s\n", msg);
  if (exit_code != 0)
    exit (exit_code);
}
