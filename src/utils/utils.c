/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:24:04 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	clear_map(t_map *map)
{
	if (map)
	{
		map->map = NULL;
		map->x_len = 0;
		map->y_len = 0;
		map->p_x = 0;
		map->p_y = 0;
	}
}

void	delete_texture_img(t_game *g)
{
	if (!g || !g->textures)
		return ;
	if (g->textures->north)
		mlx_delete_image(g->mlx, g->textures->north);
	if (g->textures->south)
		mlx_delete_image(g->mlx, g->textures->south);
	if (g->textures->east)
		mlx_delete_image(g->mlx, g->textures->east);
	if (g->textures->west)
		mlx_delete_image(g->mlx, g->textures->west);
}

void	ft_error(char *message, t_map *map, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	delete_texture_img(game);
	clear_map(map);
	if (game && game->mlx)
		mlx_terminate(game->mlx);
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
