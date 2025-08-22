/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/22 02:41:37 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	check_args(int ac, char **av)
{
	int		i;
	int		len;
	char	*filename;

	if (ac != 2)
	{
		ft_error("Usage: ./cub3D <map.cub>", NULL, NULL);
		return (0);
	}
	
	filename = av[1];
	len = ft_strlen(filename);
	
	if (len < 5)
	{
		ft_error("Filename too short to be suffixed by .cub", NULL, NULL);
		return (0);
	}
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		ft_error("File must have .cub extension", NULL, NULL);
		return (0);
	}
	i = len - 1;
	while (i >= 0 && filename[i] != '/')
		i--;
	if (ft_strcmp(filename + i + 1, ".cub") == 0)
	{
		ft_error("File cannot be just .cub", NULL, NULL);
		return (0);
	}
	return (1);
}

int	parse_file(char *file, t_game *game)
{
	int		fd;
	char	*line;

	(void)game;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file: %s\n", file);
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}