#include "server.h"

t_client *get_winner(t_server *server)
{
    t_clist	*tmp;
    tmp = server->client_list;
    while (tmp != NULL && tmp->client != NULL)
    {  
        if (tmp->client->dead == 0)
            return tmp->client;
    }
    return (NULL);
}

void check_near_object(int x, int y, t_client *client, t_server *server)
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
    } else if (cell == 'e' && x == client->x && y == client->y) {
        tmp = server->client_list;
        client->dead = 1;
        while (tmp != NULL && tmp->client != NULL)
        {  
            send_message(tmp->client, "FINISH %i\n", get_winner(server)->id, x, y);
            close_client(tmp->client, server);
            tmp = tmp->next;
        }
    }
}

void check_near_objects(t_client *client, t_server *server)
{
    int x; 
    int y;

    x = client->x;
    y = client->y;
    check_near_object(x - 1, y - 1, client, server);
    check_near_object(x - 1, y, client, server);
    check_near_object(x - 1, y + 1, client, server);
    check_near_object(x, y - 1, client, server);
    check_near_object(x, y, client, server);
    check_near_object(x, y + 1, client, server);
    check_near_object(x + 1, y - 1, client, server);
    check_near_object(x + 1, y, client, server);
    check_near_object(x + 1, y + 1, client, server);
}