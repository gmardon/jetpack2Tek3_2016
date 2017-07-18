#include "server.h"

void handle_id(char *cmd, t_client *client, t_server *server)
{

    (void) server;
    (void) cmd;
    send_message(client, "ID %i\n", client->id);
}