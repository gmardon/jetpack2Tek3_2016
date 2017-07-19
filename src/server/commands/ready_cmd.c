/*
** ready_cmd.c for id_cmd in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/server/commands/
**
** Made by nathan.bonnet@epitech.eu
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Wed Jul 19 17:40:55 2017 nathan.bonnet@epitech.eu
** Last update Wed Jul 19 17:41:02 2017 nathan.bonnet@epitech.eu
*/

#include "server.h"

void handle_ready(char *cmd, t_client *client, t_server *server)
{
    (void) cmd;
    t_clist	*tmp;
    int ready_count;

    client->state = CLIENT_STATE_READY;
    ready_count = 0;
    tmp = server->client_list;
    while (tmp != NULL && tmp->client != NULL)
    {
        if (tmp->client->state == CLIENT_STATE_READY)
            ready_count++;
        tmp = tmp->next;
    }
    tmp = server->client_list;
    if (ready_count == 2)
    {
        server->state = SERVER_STATE_STARTED;
        tmp = server->client_list;
        while (tmp != NULL && tmp->client != NULL)
        {
            send_message(tmp->client, "START\n");
            tmp = tmp->next;
        }
    }
}
