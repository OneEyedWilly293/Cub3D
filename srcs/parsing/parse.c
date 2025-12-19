/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgueon <jgueon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:19:14 by jgueon            #+#    #+#             */
/*   Updated: 2025/12/19 15:44:54 by jgueon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <unistd.h>
#include <fcntl.h>
#include <libft.h>

// /**
//  *  @brief calculates the length of a string
//  *
//  * This function counts the number of characters in a string until
//  * it reaches the null terminator '\0'.
//  *
//  * @param s: The string whose length is to be calculated
//  *
//  * @return The number of characters in
//  *	the string (excluding the null terminator)
//  */
// size_t	ft_strlen(const char *s)
// {
// 	size_t	length;

// 	length = 0;
// 	while (s[length] != '\0')
// 	{
// 		length++;
// 	}
// 	return (length);
// }

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
	int fd;

	if (argc < 2)
		return(ft_error(NO_MAP));
	if (argc > 2)
		return(ft_error(MANY_ARG_MSG));
	if (!check_extension(argv[1]))
		return (ft_error(FILE_EXT_MSG));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_error(CANT_OPEN_MAP));
	close(fd);
	return (0);
}

int main(int argc, char **argv)
{
	if (check_args(argc, argv) == 0)
		write(1, "OK: .cub file provided\n", 23);
	return (0);
}
