#include "server.h"

void handle_ready(char *cmd, t_client *client, t_server *server)
{
    (void) cmd;
    t_clist	*tmp;
    int ready_count;
    int not_ready;

    client->state = CLIENT_STATE_READY;
    not_ready = 0;
    ready_count = 0;
    tmp = server->client_list;
    while (tmp != NULL && tmp->client != NULL)
    {
        if (tmp->client->state == CLIENT_STATE_CONNECTED)
            not_ready = 1;
        else
            ready_count++;
        tmp = tmp->next;
    }
    if (!not_ready && ready_count == 2)
    {
        tmp = server->client_list;
        while (tmp != NULL && tmp->client != NULL)
        {  
            send_message(tmp->client, "START\n");
            server->state = SERVER_STATE_STARTED;
            tmp = tmp->next;
        }
    }
}