/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:40:35 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static bool	flood_fill(t_map *map, int y, int x, char **visited)
{
	if (y < 0 || y >= map->y_len || x < 0 || x >= map->x_len)
		return (false);
	if (visited[y][x])
		return (true);
	if (map->map[y][x] == ' ')
		return (false);
	if (map->map[y][x] == '1')
		return (true);
	visited[y][x] = 1;
	if (!flood_fill(map, y - 1, x, visited))
		return (false);
	if (!flood_fill(map, y + 1, x, visited))
		return (false);
	if (!flood_fill(map, y, x - 1, visited))
		return (false);
	if (!flood_fill(map, y, x + 1, visited))
		return (false);
	return (true);
}

static char	**init_visited(t_map *map)
{
	char	**visited;
	int		i;

	visited = gc_malloc(sizeof(char *) * map->y_len);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->y_len)
	{
		visited[i] = gc_malloc(sizeof(char) * map->x_len);
		if (!visited[i])
			return (NULL);
		ft_memset(visited[i], 0, map->x_len);
		i++;
	}
	return (visited);
}

void	check_path_closed(t_map *map)
{
	char	**visited;
	int		y;
	int		x;

	visited = init_visited(map);
	if (!visited)
		ft_error("Failed to allocate visited map", map, NULL);
	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (x < map->x_len)
		{
			if (!visited[y][x] && (map->map[y][x] == '0'
					|| map->map[y][x] == 'N' || map->map[y][x] == 'S'
					|| map->map[y][x] == 'E' || map->map[y][x] == 'W'))
			{
				if (!flood_fill(map, y, x, visited))
					ft_error("Map is not closed", map, NULL);
			}
			x++;
		}
		y++;
	}
}

static void	parse_color(char *line, t_color *color)
{
	char	**rgb;

	rgb = ft_split(line, ',');
	if (!rgb || ft_arraylen(rgb) != 3)
		ft_error("Invalid RGB format", NULL, NULL);
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	color->a = 255;
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		ft_error("RGB values must be between 0 and 255", NULL, NULL);
	gc_free_array((void **)rgb);
}

void	parse_config_line(char *line, t_game *g)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		g->map->north = ft_strtrim(ft_strdup(line + 3), "\n");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		g->map->south = ft_strtrim(ft_strdup(line + 3), "\n");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		g->map->west = ft_strtrim(ft_strdup(line + 3), "\n");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		g->map->east = ft_strtrim(ft_strdup(line + 3), "\n");
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, &g->textures->floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, &g->textures->ceiling);
	else
		ft_error("Invalid config line", NULL, NULL);
}
