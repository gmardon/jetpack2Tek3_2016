#include "client.h"

void validate_configuration(t_configuration *config)
{
  if (config->host == NULL)
    my_error("Unable to connect socket. Must give a valid hostname.", 84);
  if (config->port > 65535)
    my_error("Illegal port number.", 84);
}

t_configuration		*init_configuration()
{
  t_configuration	*config;

  config = my_malloc(sizeof(t_configuration));
  config->port = 4242;
  config->host = NULL;
  return (config);
}

t_configuration		*parse_args(int argc, char *argv[])
{
  t_configuration	*config;
  int			opt;

  config = init_configuration();
  while ((opt = getopt (argc, argv, "h:p:")) != -1)
    {
      if (opt == 'p')
	      config->port = atoi(optarg);
      else if (opt == 'h')
        config->host = strdup(optarg);
    }
  validate_configuration(config);
  return (config);
}
