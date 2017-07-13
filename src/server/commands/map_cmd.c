#include "server.h"

int handle_map(char *cmd, t_client *client, t_server *server)
{
    char *cells;
    int index;
    int y;
    int x;

    y = 0;
    x = 0;
    index = 0;
    cells = my_malloc((server->gamemap->height * server->gamemap->width) * sizeof(char));
    while (y < server->gamemap->height)
    {
        while (x < server->gamemap->width)
        {
            cells[index] = server->gamemap->cells[y][x];
            index++;
        }
    }
    send_message(client, "MAP %i %i %s", server->gamemap->width, server->gamemap->height, cells);
}