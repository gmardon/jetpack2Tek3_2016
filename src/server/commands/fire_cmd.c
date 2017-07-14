#include "server.h"

int handle_fire(char *cmd, t_client *client, t_server *server)
{
    client->jetpack =! client->jetpack;
}