/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:36:36 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	count_spawn_and_validate_chars(t_game *g)
{
	int		spawn_count;
	char	c;
	int		x;
	int		y;

	spawn_count = 0;
	y = -1;
	while (++y < g->map->y_len)
	{
		x = 0;
		while (g->map->map[y][x])
		{
			c = g->map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				spawn_count++;
				init_player_data(g, x, y, c);
			}
			else if (c != '0' && c != '1' && c != ' ')
				ft_error("Invalid character in map", g->map, NULL);
			x++;
		}
	}
	if (spawn_count != 1)
		ft_error("Map must have exactly 1 spawn point (N/S/E/W)", g->map, NULL);
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
	if (color->r < 0 || color->r > 255
		|| color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		ft_error("RGB values must be between 0 and 255", NULL, NULL);
	gc_free_array((void **)rgb);
}

void	parse_config_line(char *line, t_textures *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, &textures->floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, &textures->ceiling);
	else
		ft_error("Invalid config line", NULL, NULL);
}

static void	calculate_map_dimensions(t_map *map)
{
	int		i;
	size_t	len;
	size_t	max_len;

	max_len = 0;
	i = 0;
	while (i < map->y_len)
	{
		len = ft_strlen(map->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	map->x_len = max_len;
}

void	check_map(t_game *g)
{
	if (!g->map || !g->map->map || !(*g->map->map))
		ft_error("Map not loaded", g->map, NULL);
	g->map->y_len = 0;
	while (g->map->map[g->map->y_len])
		g->map->y_len++;
	calculate_map_dimensions(g->map);
	count_spawn_and_validate_chars(g);
}
