#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

sfVector2f *setPosVector()
{
  int i;
  float x;
  sfVector2f *vector;


  i = -1;
  x = 0;
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

sfSprite *Animate(sfSprite *sprite)
{
  static int i = 0;
  sfTexture *texture;

  if (i == 0)
  {
    texture = sfTexture_createFromFile("ressources/running_1.png", NULL);
    if (!texture)
        return (NULL);
    i = 1;
  }
  else if (i == 1)
  {
    texture = sfTexture_createFromFile("ressources/running_2.png", NULL);
    if (!texture)
        return (NULL);
    i = 0;
  }
    sfSprite_setTexture(sprite, texture, sfTrue);
  return(sprite);
}

sfSprite *fly(sfSprite *sprite)
{
  sfTexture *texture;

texture = sfTexture_createFromFile("ressources/rising.png", NULL);
    if (!texture)
        return (NULL);
sfSprite_setTexture(sprite, texture, sfTrue);
  return(sprite);
}

sfSprite *fall(sfSprite *sprite)
{
  sfTexture *texture;

  texture = sfTexture_createFromFile("ressources/falling.png", NULL);
      if (!texture)
          return (NULL);
  sfSprite_setTexture(sprite, texture, sfTrue);
	return(sprite);
}

int main()
{
    sfVideoMode mode = {1690, 600, 32};
    sfRenderWindow* window;
    sfSprite	*sprite0;
  	sfSprite	*sprite1;
  	sfSprite	*sprite2;
  	sfSprite	*sprite3;
    sfSprite	*sprite4;
    sfSprite	*charSprite;
    sfEvent event;
    sfVector2f *vector;
    sfVector2f charVec;
    sfTexture *texture;


		vector = setPosVector();
		charVec.x = 100;
    charVec.y = 470;

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
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

      	if(sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
      		sfRenderWindow_close(window);
        if(sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue)
        {
	  			charSprite = fly(charSprite);
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
        	charSprite = Animate(charSprite);
        else if (sfKeyboard_isKeyPressed(sfKeyZ) == sfFalse && charVec.y < 470)
        {
					charSprite = fall(charSprite);
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

        /* Update the window */
        sfRenderWindow_display(window);
      	vector = resetPosVector(vector);
        // sfSprite_setPosition(secSprite, vector[i]);
    }

    /* Cleanup resources */
    	sfSprite_destroy(sprite0);
      sfSprite_destroy(sprite1);
      sfSprite_destroy(sprite2);
      sfSprite_destroy(sprite3);
      sfSprite_destroy(sprite4);
      sfSprite_destroy(charSprite);
    sfRenderWindow_destroy(window);
  	sfTexture_destroy(texture);
    return EXIT_SUCCESS;
}
