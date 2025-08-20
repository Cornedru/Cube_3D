/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 15:09:12 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	check_args(int ac, char **av)
{
	int		i;
	char	*filename;

	i = 0;
	filename = av[1];
	if (ac != 2)
		ft_error("Error\nUsage: ./cub3D <map.cub>\n", NULL, NULL);
	else if (ft_strlen(filename) < 5)
		ft_error("Filename to short to be suffixed by .cub", NULL, NULL);
	else if (ft_strcmp(av[1] + i - 4, ".cub"))
		ft_error("Error\nFile must have .cub extension\n", NULL, NULL);
	else
	{
		while (av[1][i])
		{
			if (av[1][i] == '/')
				filename = &av[1][i + 1];
			i++;
		}
		if (!ft_strncmp(filename, ".ber", 4))
			ft_error("file can not be just .ber", NULL, NULL);
	}
	return (i);
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
