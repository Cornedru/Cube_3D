/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 18:48:47 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	count_spawn_and_validate_chars(t_map *map)
{
	int		spawn_count;
	char	c;
	int		x;
	int		y;

	spawn_count = 0;
	y = 0;
	while (y < map->y_len)
	{
		x = 0;
		while (map->map[y][x])
		{
			c = map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				spawn_count++;
				map->p_x = x;
				map->p_y = y;
			}
			else if (c != '0' && c != '1' && c != ' ')
				ft_error("Invalid character in map", map, NULL);
			x++;
		}
		y++;
	}
	if (spawn_count != 1)
		ft_error("Map must have exactly 1 spawn point (N/S/E/W)", map, NULL);
}

void	parse_color(char *line, t_color *color)
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

// static void	is_rectangle(t_map *map)
// {
// 	int	i;
// 	size_t	len;

// 	len = ft_strlen(map->map[0]);
// 	map->x_len = len;
// 	i = 1;
// 	while (i < map->y_len)
// 	{
// 		if (ft_strlen(map->map[i]) != len)
// 			ft_error("The map is not rectangular", map, NULL);
// 		i++;
// 	}
// }

void	check_map(t_map *map)
{
	if (!map || !map->map || !(*map->map))
		ft_error("Map not loaded", map, NULL);
	map->y_len = 0;
	while (map->map[map->y_len])
		map->y_len++;
	count_spawn_and_validate_chars(map);
}
