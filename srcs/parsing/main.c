#include "parse.h"
#include "libft.h"

// MAIN TO PRINT IDENTIFER(F and C) if successful
int main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (check_args(argc, argv))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(CANT_OPEN_MAP));
	if (find_color_lines(fd, &game))
		return (close(fd), 1);
	close(fd);

	// Print result
	ft_putstr_fd("Floor: ", 1);
	ft_putnbr_fd(game.floor.r, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(game.floor.g, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(game.floor.b, 1);
	ft_putstr_fd("\n", 1);

	ft_putstr_fd("Ceiling: ", 1);
	ft_putnbr_fd(game.ceiling.r, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(game.ceiling.g, 1);
	ft_putstr_fd(",", 1);
	ft_putnbr_fd(game.ceiling.b, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

// MAIN TO PRINT WHOLE MAP on screen if it pass parser
// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (check_args(argc, argv))
//         return (1);
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//         return (ft_error(CANT_OPEN_MAP));

//     line = get_line(fd);
//     int count = 0;
//     while (line && count < 20)  // first 20 lines
//     {
//         ft_putstr_fd("[LINE ", 1);
//         ft_putnbr_fd(count, 1);
//         ft_putstr_fd("] '", 1);
//         ft_putstr_fd(line, 1);
//         ft_putstr_fd("' (len=", 1);
//         ft_putnbr_fd(ft_strlen(line), 1);
//         ft_putstr_fd(")\n", 1);
//         free(line);
//         line = get_line(fd);
//         count++;
//     }
//     close(fd);
//     return (0);
// }
