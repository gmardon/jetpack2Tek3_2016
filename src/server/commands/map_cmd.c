/*
** map_cmd.c for map_cmd in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/commands/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:41:13 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:41:23 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

void handle_map(char *cmd, t_client *client, t_server *server)
{
    (void) cmd;
    char *cells;
    int index;
    int y;
    int x;

    y = 0;
    index = 0;
    cells = my_malloc((server->gamemap->height * server->gamemap->width)
     * (sizeof(char) + 1));
    while (y < server->gamemap->height)
    {
        x = 0;
        while (x < server->gamemap->width)
        {
            cells[index] = server->gamemap->cells[y][x];
            index++;
            x++;
        }
        y++;
    }
    send_message(client, "MAP %i %i %s\n", server->gamemap->width,
     server->gamemap->height, cells);
}
