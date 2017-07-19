#include "client.h"

void handle_id(char **cmd, t_client *client)
{
    (void) client;
    client->id = atoi(cmd[1]);
    printf("CLIENT ID: %i\n", client->id);
}