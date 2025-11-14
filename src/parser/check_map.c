/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/30 00:04:28 by oligrien         ###   ########.fr       */
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

static void	validate_map_borders(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map->y_len)
	{
		x = 0;
		while (g->map->map[y][x])
		{
			if (g->map->map[y][x] == '0' || g->map->map[y][x] == 'N'
				|| g->map->map[y][x] == 'S' || g->map->map[y][x] == 'E'
				|| g->map->map[y][x] == 'W')
			{
				check_cell_surroundings(g, x, y);
			}
			x++;
		}
		y++;
	}
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
	validate_map_borders(g);
}
