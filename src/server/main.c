#include "server.h"

int main(int argc, char *argv[])
{
    printf("START SERVER JETPACK2TEK3\n");
    t_configuration	*config;
    t_server *server;
    config = parse_args(argc, argv);
    server = create_server(config);
    start_server(server);
    return (0);
}