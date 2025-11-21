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

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = gc_malloc(sizeof(char *) * (map->y_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->y_len)
	{
		copy[i] = gc_strdup(map->map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map, int x, int y, t_map *orig_map)
{
	size_t	line_len;

	if (y < 0 || y >= orig_map->y_len)
		ft_error("Map is not closed: out of bounds (Y)", orig_map, NULL);
	if (x < 0)
		ft_error("Map is not closed: out of bounds (X < 0)", orig_map, NULL);
	line_len = ft_strlen(map[y]);
	if (x >= (int)line_len)
		ft_error("Map is not closed: reached end of line (space)", orig_map,
			NULL);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		ft_error("Map is not closed: found space", orig_map, NULL);
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, orig_map);
	flood_fill(map, x - 1, y, orig_map);
	flood_fill(map, x, y + 1, orig_map);
	flood_fill(map, x, y - 1, orig_map);
}

void	check_path_closed(t_map *map)
{
	char	**map_copy;
	int		start_x;
	int		start_y;

	start_x = map->p_x;
	start_y = map->p_y;
	map_copy = copy_map(map);
	if (!map_copy)
		ft_error("Unable to copy map", map, NULL);
	flood_fill(map_copy, start_x, start_y, map);
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
