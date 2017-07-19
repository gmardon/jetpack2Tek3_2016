/*
** my_malloc.c for my_malloc in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 16:39:34 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 16:39:41 2017 nathan.bonnet@epitech.eu
*/

#include "jetpack.h"

void	*my_malloc(int size)
{
  void	*ref;

  if (!(ref = malloc(size)))
    exit(84);
  return (ref);
}
