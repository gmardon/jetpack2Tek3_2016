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
    cells = my_malloc((server->gamemap->height * server->gamemap->width) * (sizeof(char) + 1));
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
    send_message(client, "MAP %i %i %s\n", server->gamemap->width, server->gamemap->height, cells);
}