/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:40:38 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/29 20:33:41 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

static void	print_colors(t_game game)
{
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
}

static void	print_textures(t_game game)
{
	ft_putstr_fd("NO: ", 1);
	ft_putstr_fd(game.tex.no, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("SO: ", 1);
	ft_putstr_fd(game.tex.so, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("WE: ", 1);
	ft_putstr_fd(game.tex.we, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("EA: ", 1);
	ft_putstr_fd(game.tex.ea, 1);
	ft_putstr_fd("\n", 1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (check_args(argc, argv))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(CANT_OPEN_MAP));
	if (find_texture_lines(fd, &game))
		return (close(fd), 1);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(CANT_OPEN_MAP));
	if (find_color_lines(fd, &game))
		return (close(fd), 1);
	close(fd);
	print_textures(game);
	print_colors(game);
	return (0);
}
