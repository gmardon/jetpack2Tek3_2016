#include "server.h"

t_client *get_winner(t_server *server)
{
    t_clist	*tmp;
    int best_score;
    t_client *best_player;

    tmp = server->client_list;
    best_player = NULL;
    best_score = 0;
    while (tmp != NULL && tmp->client != NULL)
    {  
        printf("%i from %i\n", tmp->client->score, tmp->client->id);
        if (tmp->client->dead == 1)
        {
            printf("%i is dead\n", tmp->client->id);
            tmp = server->client_list;
            while (tmp != NULL && tmp->client != NULL)
            {
                if (tmp->client->dead == 0)
                    return (tmp->client);
                
                tmp = tmp->next;
            }
        }
        else if (best_score < tmp->client->score)
        {
            best_player = tmp->client;
            best_score = tmp->client->score;
        }
        tmp = tmp->next;
    }
    return (best_player);
}

void check_near_object(int x, int y, t_client *client, t_server *server)
{
    t_clist	*tmp;
    char cell;
    t_client winner;
    
    if (x > server->gamemap->width || y > server->gamemap->height)
        return;
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
        if (server->winner == NULL)
            server->winner = get_winner(server);
        server->state = SERVER_STATE_FINISHED;
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

void check_position(t_client *client, t_server *server)
{
    t_clist	*tmp;

    if (client->x > server->gamemap->width && server->winner == NULL)
    {
        server->winner = get_winner(server);
        server->state = SERVER_STATE_FINISHED;
    }
}