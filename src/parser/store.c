/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:14:05 by ndehmej           #+#    #+#             */
/*   Updated: 2025/08/22 02:23:00 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	skip_config_lines(int fd, t_textures *textures, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(fd);
		if (!line)
			ft_error("Missing configuration lines", map, NULL);
		if (line[0] != '\n')
		{
			parse_config_line(line, textures);
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

	// Use garbage collector for the map array
	map->map = gc_malloc(sizeof(char *) * (map->y_len + 1));
	if (!map->map)
		ft_error("Malloc failed", map, NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			// Use ft_strtrim and then track with gc
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

void	store_map(t_map *map, t_textures *textures, char **av)
{
	int	fd;

	// Initialize textures structure
	ft_memset(textures, 0, sizeof(t_textures));
	
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("File not found", map, NULL);
	skip_config_lines(fd, textures, map);
	count_map_lines(fd, map);
	close(fd);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		ft_error("File not found", map, NULL);
	skip_config_lines(fd, textures, map);
	load_map_lines(fd, map);
	close(fd);
}