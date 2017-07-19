/*
** window.c for window in /home/bonnet_n/tek2/rendu/Tek2/synthesis/jetpack2Tek3_2016/src/client/
**
** Made by Nathan
** Login   <nathan.bonnet@epitech.eu@epitech.eu>
**
** Started on  Tue Jul 18 15:15:53 2017 Nathan
** Last update Wed Jul 19 14:47:43 2017 Nathan
*/


#include <stdlib.h>

#include "client.h"


sfVector2f *setPosVector()
{
  int i;
  sfVector2f *vector;


  i = -1;
  if ((vector = malloc(sizeof(sfVector2f) * 6)) == NULL)
    return (NULL);
  while (++i != 6)
  {
    vector[i].x = (423 * i);
    vector[i].y = 0;
  }
  return(vector);
}

sfVector2f *resetPosVector(sfVector2f *vector)
{
  for (int i = 0; i != 6; i++)
  {
    vector[i].x -= 0.5;
    if (vector[i].x == -423)
    	vector[i].x = 1692;
  }
  return(vector);
}

sfSprite *Animate(sfSprite *sprite, sfTexture *texture1, sfTexture *texture2)
{
  static int i = 0;
  if (i == 0)
    {
      sfSprite_setTexture(sprite, texture1, sfTrue);
      i = 1;
    }
  else if (i == 1)
  {
    sfSprite_setTexture(sprite, texture2, sfTrue);
    i = 0;
  }
  return(sprite);
}

sfTexture *createTxture(char *pth)
{
  sfTexture *texture;

  texture = sfTexture_createFromFile(pth, NULL);
  if (!texture)
    exit(84);
  return(texture);
}

int makeWindow(t_client *client)
{
  sfVideoMode mode = {1690, 600, 30};
  sfRenderWindow* window;
  sfSprite	*sprite0;
  sfSprite	*sprite1;
  sfSprite	*sprite2;
  sfSprite	*sprite3;
  sfSprite	*sprite4;
  sfSprite	*charSprite;
  sfEvent event;
  sfFont* font;
  sfText* text;
  sfVector2f *vector;
  sfVector2f charVec;
  sfTexture *texture;
  sfTexture *texture1;
  sfTexture *texture2;
  sfTexture *fall;
  sfTexture *fly;
  // char *buff;

  texture1 = createTxture("ressources/running_1.png");
  texture2 = createTxture("ressources/running_2.png");
  fall = createTxture("ressources/falling.png");
  fly = createTxture("ressources/rising.png");

	vector = setPosVector();
	charVec.x = 100;
  charVec.y = 470;

  // sprintf(buff, "%d", 123);

  font = sfFont_createFromFile("ressources/fontJ2T3.ttf");
  if (!font)
      return EXIT_FAILURE;
  text = sfText_create();
  sfText_setString(text, "SCORE: 0");
  sfText_setFont(text, font);
  sfText_setCharacterSize(text, 25);
  sfText_setColor(text, sfYellow);

  /* Create the main window */
  window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
  if (!window)
      return EXIT_FAILURE;

  texture = sfTexture_createFromFile("ressources/Background.png", NULL);
  if (!texture)
      return (EXIT_FAILURE);

  sprite0 = sfSprite_create();
  sprite1 = sfSprite_create();
  sprite2 = sfSprite_create();
  sprite3 = sfSprite_create();
  sprite4 = sfSprite_create();
  charSprite = sfSprite_create();

  sfSprite_setTexture(sprite0, texture, sfTrue);
  sfSprite_setTexture(sprite1, texture, sfTrue);
  sfSprite_setTexture(sprite2, texture, sfTrue);
  sfSprite_setTexture(sprite3, texture, sfTrue);
  sfSprite_setTexture(sprite4, texture, sfTrue);



  // /* Start the game loop */
  while (sfRenderWindow_isOpen(window))
  {
    handle_io(client);
    /* Process events */
    while (sfRenderWindow_pollEvent(window, &event))
    {
        /* Close window : exit */
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }

    if(sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
    	sfRenderWindow_close(window);
    if(sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue && charVec.y >= 70)
    {
      sfSprite_setTexture(charSprite, fly, sfTrue);
      charVec.y -= 0.5;
    }

    if(sfKeyboard_isKeyPressed(sfKeyO) == sfTrue)
			charVec.y = 470;


    sfSprite_setPosition(sprite0, vector[0]);
    sfSprite_setPosition(sprite1, vector[1]);
    sfSprite_setPosition(sprite2, vector[2]);
    sfSprite_setPosition(sprite3, vector[3]);
    sfSprite_setPosition(sprite4, vector[4]);
    sfSprite_setPosition(charSprite, charVec);
    if (charVec.y == 470)
    	charSprite = Animate(charSprite, texture1, texture2);
    else if (sfKeyboard_isKeyPressed(sfKeyZ) == sfFalse && charVec.y < 470)
    {
      sfSprite_setTexture(charSprite, fall, sfTrue);
      charVec.y += 0.50;
    }

    /* Clear the screen */
    sfRenderWindow_clear(window, sfBlack);

    /* Draw the sprite */
    sfRenderWindow_drawSprite(window, sprite0, NULL);
    sfRenderWindow_drawSprite(window, sprite1, NULL);
    sfRenderWindow_drawSprite(window, sprite2, NULL);
    sfRenderWindow_drawSprite(window, sprite3, NULL);
    sfRenderWindow_drawSprite(window, sprite4, NULL);
    sfRenderWindow_drawSprite(window, charSprite, NULL);
    /* Draw the text */
    sfRenderWindow_drawText(window, text, NULL);


    /* Update the window */
    sfRenderWindow_display(window);
    vector = resetPosVector(vector);
    // sfSprite_setPosition(secSprite, vector[i]);
  }

  /* Cleanup resources */
  sfSprite_destroy(sprite0);
  sfSprite_destroy(sprite1);
  sfSprite_destroy(sprite2);
  sfText_destroy(text);
  sfFont_destroy(font);
  sfSprite_destroy(sprite3);
  sfSprite_destroy(sprite4);
  sfSprite_destroy(charSprite);
  sfRenderWindow_destroy(window);
  sfTexture_destroy(texture);
  return EXIT_SUCCESS;
}
