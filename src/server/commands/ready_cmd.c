#include "server.h"

int handle_ready(char *cmd, t_client *client, t_server *server)
{
    client->state = CLIENT_STATE_READY;
}