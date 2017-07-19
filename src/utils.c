/*
** utils.c for utils in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016
** 
** Made by bonnet_n
** Login   <bonnet_n>
** 
** Started on  Wed Jul 19 16:43:45 2017 bonnet_n
** Last update Wed Jul 19 16:43:52 2017 bonnet_n
*/

#include "jetpack.h"

char		**strsplit(const char* str, const char* delim) 
{
  char		*s = strdup(str);
  size_t	tokens_alloc = 1;
  size_t	tokens_used = 0;
  char		**tokens = calloc(tokens_alloc, sizeof(char*));
  char		*token, *rest = s;
  while ((token = strsep(&rest, delim)) != NULL)
    {
    if (tokens_used == tokens_alloc)
      {
	tokens_alloc *= 2;
	tokens = realloc(tokens, tokens_alloc * sizeof(char*));
      }
    tokens[tokens_used++] = strdup(token);
  }
  if (tokens_used == 0)
    {
      free(tokens);
      tokens = NULL;
    }
  else
    tokens = realloc(tokens, tokens_used * sizeof(char*));
  free(s);
  return tokens;
}
