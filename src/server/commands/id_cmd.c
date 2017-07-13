#include "server.h"

int handle_id(char *cmd, t_client *client, t_server *server)
{
    send_message(client, "ID %i\n", client->id);
}