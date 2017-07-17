#include "server.h"

void check_coin(int x, int y, t_client *client, t_server *server)
{
    char cell = server->gamemap->cells[y][x];
    if (cell == 'c')
    {
        client->score++;
        server->gamemap->cells[y][x] = 'o';
    } else if (cell == 'e') {
        
    }
}