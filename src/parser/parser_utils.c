/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:34:30 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static bool	ft_isnum(char *str)
{
	while (str)
	{
		if (*str < '0' || *str > '9')
			return (true);
		str++;
	}
	return (false);
}

int	check_args(t_game *g, int ac, char **av)
{
	int		i;
	int		len;
	char	*filename;

	if (ac < 2 || ac > 4)	// FOR EVAL: STRCTLY 2 !!
		return (ft_error("Usage: ./cub3D <map.cub> [w] [h]", NULL, NULL), 0);
	filename = av[1];
	len = ft_strlen(filename);
	if (len < 5)
		return (ft_error("Filename too short to be suffixed by .cub", NULL, \
			NULL), 0);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (ft_error("File must have .cub extension", NULL, NULL), 0);
	i = len - 1;
	while (i >= 0 && filename[i] != '/')
		i--;
	if (ft_strcmp(filename + i + 1, ".cub") == 0)
		return (ft_error("File cannot be just .cub", NULL, NULL), 0);

	// REMOVE THIS FOR EVALUATION !!
	if (ft_isnum(av[2]) && ft_isnum(av[3]))
	{
		g->res_w = ft_atoi(av[2]);
		g->res_h = ft_atoi(av[3]);
		printf("res_w = %d\nres_h = %d\n", g->res_w, g->res_h);
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
