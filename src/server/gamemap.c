/*
** gamemap.c for gamemap in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:22:23 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:32:43 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

void	check_if_exist(char *filepath)
{
  if (fopen(filepath, "r") == NULL)
    {
      perror("Error opening file");
      my_error(NULL, 84);
    }
}

int	check_char(char c)
 {
  if (c == 'c' || c == 'e' || c == '_')
    return (0);
  return (1);
}

void	read_map(char *filepath, t_gamemap *gamemap)
{
  char	**map;
  char	*buffer;
  int	fd;
  int	index;
  int	subidx;

  index = 0;
  fd = fileno(fopen(filepath, "r"));
  map = my_malloc(sizeof(char*) * 2 * (gamemap->height));
  while ((buffer = get_next_line(fd)))
    {
      map[index] = strdup(buffer);
      subidx = 0;
      while (map[index][subidx])
        {
	  if (check_char(map[index][subidx]) == 0)
	    subidx++;
	  else
	    my_error("Incorrect map.", 84);
        }
      index++;
    }
  map[index] = 0;
  gamemap->cells = map;
}

void	retreive_map_size(char *filepath, t_gamemap *gamemap)
{
  int	height;
  int	width;
  int	fd;
  char	*buffer;

  height = 0;
  width = -1;
  fd = fileno(fopen(filepath, "r"));
  while ((buffer = get_next_line(fd)))
    {
      if (width == -1)
	width = strlen(buffer);
      height++;
    }
  gamemap->width = width;
  gamemap->height = height;
}

t_gamemap	*init_map(char *filepath)
{
  check_if_exist(filepath);
  t_gamemap *gamemap = my_malloc(sizeof(t_gamemap));
  gamemap->width = 0;
  gamemap->height = 0;
  retreive_map_size(filepath, gamemap);
  if (gamemap->width == -1 && gamemap->height == 0)
    my_error("Empty map file.", 84);
  read_map(filepath, gamemap);

  return (gamemap);
}
