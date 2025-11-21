/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:34:30 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	calculate_map_dimensions(t_map *map)
{
	size_t	len;
	size_t	max_len;
	int		i;

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

static void	normalize_map(t_map *map)
{
	char	*new;
	int		len;
	int		i;
	int		j;

	i = 0;
	while (i < map->y_len)
	{
		len = ft_strlen(map->map[i]);
		if (len < map->x_len)
		{
			new = gc_malloc(sizeof(char) * (map->x_len + 1));
			j = -1;
			while (++j < (int)len)
				new[j] = map->map[i][j];
			while (j < (int)map->x_len)
				new[j++] = '1';
			new[map->x_len] = '\0';
			map->map[i] = new;
		}
		i++;
	}
}

static void	count_spawn_and_validate_chars(t_game *g)
{
	int		spawn;
	char	c;
	int		x;
	int		y;

	spawn = 0;
	y = -1;
	while (++y < g->map->y_len)
	{
		x = 0;
		while (g->map->map[y][x])
		{
			c = g->map->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				spawn++;
				init_player_data(g, x, y, c);
			}
			else if (c != '0' && c != '1' && c != ' ' && c != '\t')
				ft_error("Invalid character in map", g->map, NULL);
			x++;
		}
	}
	if (spawn != 1)
		ft_error("Map must have exactly 1 spawn point", g->map, NULL);
}

void	check_map(t_game *g)
{
	if (!g->map || !g->map->map)
		ft_error("Map not loaded", g->map, NULL);
	g->map->y_len = 0;
	while (g->map->map[g->map->y_len])
		g->map->y_len++;
	calculate_map_dimensions(g->map);
	normalize_map(g->map);
	count_spawn_and_validate_chars(g);
	check_path_closed(g->map);
}
