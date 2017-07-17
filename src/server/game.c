#include "server.h"

void check_coin(int x, int y, t_client *client, t_server *server)
{
    t_clist	*tmp;
    char cell;
    
    cell = server->gamemap->cells[y][x];
    if (cell == 'c')
    {
        client->score++;
        server->gamemap->cells[y][x] = 'o';
        tmp = server->client_list;
        while (tmp != NULL && tmp->client != NULL)
        {  
            send_message(tmp->client, "COIN %i %i %i\n", client->id, x, y);
            tmp = tmp->next;
        }
    } else if (cell == 'e') {
        
    }
}