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

void	check_vertical(t_game *g, int x, int y)
{
	if (y > 0)
	{
		if (x >= (int)ft_strlen(g->map->map[y - 1])
			|| g->map->map[y - 1][x] == ' ')
			ft_error("Map not closed: space above playable area", g->map, NULL);
	}
	if (y < g->map->y_len - 1)
	{
		if (x >= (int)ft_strlen(g->map->map[y + 1])
			|| g->map->map[y + 1][x] == ' ')
			ft_error("Map not closed: space below playable area", g->map, NULL);
	}
}

void	check_horizontal(t_game *g, int x, int y, size_t line_len)
{
	if (x > 0 && g->map->map[y][x - 1] == ' ')
		ft_error("Map not closed: space left of playable area", g->map, NULL);
	if (x < (int)line_len - 1 && g->map->map[y][x + 1] == ' ')
		ft_error("Map not closed: space right of playable area", g->map, NULL);
}

void	check_edges(t_game *g, int x, int y, size_t line_len)
{
	if (y == 0 || y == g->map->y_len - 1)
		ft_error("Map must be surrounded by walls (top/bottom edge)",
			g->map, NULL);
	if (x == 0 || x == (int)line_len - 1)
		ft_error("Map must be surrounded by walls (left/right edge)",
			g->map, NULL);
}

void	check_cell_surroundings(t_game *g, int x, int y)
{
	size_t	line_len;
	char	c;

	c = g->map->map[y][x];
	if (c == '1' || c == ' ')
		return ;
	line_len = ft_strlen(g->map->map[y]);
	check_edges(g, x, y, line_len);
	check_vertical(g, x, y);
	check_horizontal(g, x, y, line_len);
}
