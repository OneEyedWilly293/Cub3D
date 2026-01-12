/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:19:14 by jgueon            #+#    #+#             */
/*   Updated: 2026/01/10 18:45:05 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_err(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(2, &s[i], 1);
		i++;
	}
}

int	ft_error(const char *msg)
{
	ft_putstr_err("Error\n");
	ft_putstr_err(msg);
	return (1);
}

static int	check_extension(const char *file)
{
	int	len;
	int	ext_len;

	len = ft_strlen(file);
	ext_len = ft_strlen(MAP_EXTENSION);
	if (len < ext_len)
		return (0);
	if (file[len - 4] != MAP_EXTENSION[0])
		return (0);
	if (file[len - 3] != MAP_EXTENSION[1])
		return (0);
	if (file[len - 2] != MAP_EXTENSION[2])
		return (0);
	if (file[len - 1] != MAP_EXTENSION[3])
		return (0);
	return (1);
}

int check_args(int argc, char **argv)
{
	if (argc < 2)
		return(ft_error(NO_MAP));
	if (argc > 2)
		return (ft_error(INVALID_ARG_MSG));
	if (!check_extension(argv[1]))
		return (ft_error(FILE_EXT_MSG));
	return (0);
}
