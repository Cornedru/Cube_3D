/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:14:05 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/27 23:09:24 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	skip_config_lines(int fd, t_game *g)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			ft_error("Missing configuration lines", g->map, NULL);
		if (line[0] != '\n')
		{
			parse_config_line(line, g->textures);
			i++;
		}
		free(line);
	}
}

static void	count_map_lines(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
			map->y_len++;
		free(line);
		line = get_next_line(fd);
	}
}

static void	load_map_lines(int fd, t_map *map)
{
	char	*line;
	int		i;

	map->map = gc_malloc(sizeof(char *) * (map->y_len + 1));
	if (!map->map)
		ft_error("Malloc failed", map, NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			char *trimmed = ft_strtrim(line, "\n");
			map->map[i] = gc_strdup(trimmed);
			free(trimmed);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	map->map[i] = NULL;
}

void	store_map(t_game *g, char **av)
{
	int	fd;

	g->textures = gc_malloc(sizeof(t_textures));
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("File not found", g->map, NULL);
	skip_config_lines(fd, g);
	count_map_lines(fd, g->map);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("File not found", g->map, NULL);
	skip_config_lines(fd, g);
	load_map_lines(fd, g->map);
	close(fd);
}
