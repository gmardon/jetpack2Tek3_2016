#include "server.h"

void read_map(char *filepath, t_gamemap *gamemap)
{
    char** map;
    char *buffer;
    int fd;
    int index;

    index = 0;
    fd = fileno(fopen(filepath, "r"));
    map = my_malloc(sizeof(char*) * 2 * (gamemap->height));
    while ((buffer = get_next_line(fd))) 
    {
        map[index] = strdup(buffer);
        index++;
    }
    map[index] = 0;
    gamemap->cells = map;
}

void retreive_map_size(char *filepath, t_gamemap *gamemap)
{
    int height;
    int width;
    int fd;
    char *buffer;

    height = 0;
    width = -1;
    fd = fileno(fopen(filepath, "r"));
    while ((buffer = get_next_line(fd)))
    {
        if (width == -1)
            width = strlen(buffer);
        height++;    
    }
    gamemap->width = width;
    gamemap->height = height;
}

t_gamemap *init_map(char *filepath)
{
    t_gamemap *gamemap = my_malloc(sizeof(t_gamemap));
    gamemap->width = 0;
    gamemap->height = 0;
    retreive_map_size(filepath, gamemap);
    read_map(filepath, gamemap);

    return (gamemap);
}
