#include "server.h"

void validate_configuration(t_configuration *config)
{
  if (config->port < 1000)
    my_error("Unable to bind socket. Ports under 1000 are reserved.", -1);
  if (config->port > 65535)
    my_error("Illegal port number.", -1);
  if (config->map == NULL)
    my_error("You must provide a map file.", -1);
}

t_configuration		*init_configuration()
{
  t_configuration	*config;

  config = my_malloc(sizeof(t_configuration));
  config->port = 4242;
  config->gravity = 100;
  config->map = NULL;
  return (config);
}

t_configuration		*parse_args(int argc, char *argv[])
{
  t_configuration	*config;
  int			opt;

  config = init_configuration();
  while ((opt = getopt (argc, argv, "p:g:m:")) != -1)
    {
      if (opt == 'p')
	      config->port = atoi(optarg);
      else if (opt == 'g')
        config->gravity = atoi(optarg);
      else if (opt == 'm')
	      config->map = strdup(optarg);
    }
  validate_configuration(config);
  return (config);
}
