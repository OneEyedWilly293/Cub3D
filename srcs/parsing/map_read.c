
#include "parse.h"
#include "libft.h"

// strlen but with a NULL check(and int instead of size_t)
static int  row_len(char *s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

static int  fill_row(t_game *game, int y, char *line)
{
    char    *row;

    row = (char *)malloc((size_t)game->map_w + 1);
    if (!row)
        return (ft_error("Malloc failed\n"));
    ft_memset(row, ' ', (size_t)game->map_w);
    row[game->map_w] = '\0';
    ft_memcpy(row, line, (size_t)row_len(line));
    game->map[y] = row;
    return (0);
}

void    free_map(char **map)
{
    int i;

    i = 0;
    while (map && map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

static int  alloc_map(t_game *game)
{
    game->map = (char **)malloc(sizeof(char *) * (size_t)(game->map_h + 1));
    if (!game->map)
        return (ft_error("Malloc failed\n"));
    game->map[game->map_h] = NULL;
    return (0);
}

int read_map(int fd, t_game *game)
{
    char    *line;
    int     y;

    game->map_h = 0;
    game->map_w = 0;
    line = get_line(fd);
    while (line)
    {
        if (row_len(line) > game->map_w)
            game->map_w = row_len(line);
        game->map_h++;
        free(line);
        line = get_line(fd);
    }
    if (game->map_h == 0)
        return (ft_error(EMPTY_MSG));
    if (alloc_map(game))
        return (1);
    close(fd);
    fd = -1;
    return (0);
}