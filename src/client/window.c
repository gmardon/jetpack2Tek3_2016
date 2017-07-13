#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdlib.h>

int main()
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfSprite* sprite;
    sfFont* font;
    sfText* text;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return EXIT_FAILURE;

    /* Load a sprite to display */
    sprite = sfSprite_create();

    /* Create a graphical text to display */
    font = sfFont_createFromFile("arial.ttf");
    if (!font)
        return EXIT_FAILURE;
    text = sfText_create();
    sfText_setString(text, "#JetPackVie");
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);

    /* Load a music to play */
    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the sprite */
        sfRenderWindow_drawSprite(window, sprite, NULL);

        /* Draw the text */
        sfRenderWindow_drawText(window, text, NULL);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfText_destroy(text);
    sfFont_destroy(font);
    sfSprite_destroy(sprite);
    sfRenderWindow_destroy(window);

    return EXIT_SUCCESS;
}
