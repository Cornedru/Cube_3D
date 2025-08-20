/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 14:25:34 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	clear_map(t_map *map)
{
	int	i;

	if (map && map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			map->map[i] = NULL;
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
}

void	delete_texture_img(t_game *game)
{
	if (!game)
		return ;
	if (game->p)
		mlx_delete_image(game->mlx, game->p);
	if (game->c)
		mlx_delete_image(game->mlx, game->c);
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
	if (game->door)
		mlx_delete_image(game->mlx, game->door);
}

void	ft_error(char *message, t_map *map, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	delete_texture_img(game);
	clear_map(map);
	if (game && game->mlx)
		mlx_terminate(game->mlx);
	exit(1);
}
