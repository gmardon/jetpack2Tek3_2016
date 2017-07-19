#include "client.h"

int main(int argc, char *argv[])
{
    t_configuration	*config;
    t_client *client;
    config = parse_args(argc, argv);
    client = create_client(config);
    start_client(client);
    return (0);
}