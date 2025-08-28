/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:36:48 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	clear_map(t_map *map)
{
	// No need to manually free if using garbage collector
	// The gc will handle cleanup when gc_destroy() is called
	if (map)
	{
		map->map = NULL;
		map->x_len = 0;
		map->y_len = 0;
		map->p_x = 0;
		map->p_y = 0;
	}
}

/* void	delete_texture_img(t_game *game)
{
	if (!game)
		return ;
	if (game->p)
		mlx_delete_image(game->mlx, game->p);
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
} */

void	ft_error(char *message, t_map *map, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	// delete_texture_img(game);
	clear_map(map);
	if (game && game->mlx)
		mlx_terminate(game->mlx);
	// Clean up all garbage collector allocations
	gc_destroy();
	exit(1);
}

bool	is_oob(t_game *g, int map_x, int map_y)
{
	return (!(map_x >= 0 && map_x < g->map->x_len && map_y >= 0
		&& map_y < g->map->y_len));
}

void	init_player_data(t_game *g, int x, int y, char c)
{
	g->pl->pos_x = x + 0.5;
	g->pl->pos_y = y + 0.5;
	g->pl->start_dir = c;
}
