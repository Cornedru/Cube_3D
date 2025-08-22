/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/22 02:31:47 by ndehmej          ###   ########.fr       */
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

void	delete_texture_img(t_game *game)
{
	if (!game)
		return ;
	if (game->p)
		mlx_delete_image(game->mlx, game->p);
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
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
	// Clean up all garbage collector allocations
	gc_destroy();
	exit(1);
}