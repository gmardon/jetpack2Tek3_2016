#include "server.h"

void handle_fire(char *cmd, t_client *client, t_server *server)
{
    (void) server;
    (void) cmd;
    client->jetpack =! client->jetpack;  
}