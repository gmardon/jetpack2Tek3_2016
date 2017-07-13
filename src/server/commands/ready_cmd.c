#include "server.h"

int handle_ready(char *cmd, t_client *client, t_server *server)
{
    t_clist	*tmp;
    int not_ready;

    client->state = CLIENT_STATE_READY;
    not_ready = 0;
    tmp = server->client_list;
    while (tmp != NULL)
    {
        if (tmp->client->state == CLIENT_STATE_CONNECTED)
            not_ready = 1;
        tmp = tmp->next;
    }
    if (!not_ready)
    {
        tmp = server->client_list;
        while (tmp != NULL)
        {  
            send_message(tmp->client, "START\n");
            tmp = tmp->next;
        }
    }
    
}