#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

typedef struct s_coin
{
	sfSprite* sprite;
	sfTexture *texture;
	sfVector2f vector;
  struct s_coin *next;
} t_coin;

typedef t_coin  *t_list;

#endif
