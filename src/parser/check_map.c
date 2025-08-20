/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 15:13:32 by ndehmej          ###   ########.fr       */
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
	// is_rectangle(map);
	count_spawn_and_validate_chars(map);
}
