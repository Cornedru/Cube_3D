/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 15:13:39 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (map->y_len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->y_len)
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_copy(char **map_copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(map_copy[i++]);
	free(map_copy);
}

static void	flood_fill(char **map, int x, int y, t_map *orig_map)
{
	if (y < 0 || y >= orig_map->y_len || x < 0 || !map[y][x])
		ft_error("Map is not closed: out of bounds", orig_map, NULL);
	if (map[y][x] == ' ' || map[y][x] == '\0')
		ft_error("Map is not closed: found space or invalid char", orig_map,
			NULL);
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
	free_copy(map_copy, map->y_len);
}
