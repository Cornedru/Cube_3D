/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/22 02:30:48 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	update_pos(mlx_key_data_t key, t_game *game)
{
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_UP)
		(game->p_y)--;
	else if (key.key == MLX_KEY_A || key.key == MLX_KEY_LEFT)
		(game->p_x)--;
	else if (key.key == MLX_KEY_S || key.key == MLX_KEY_DOWN)
		(game->p_y)++;
	else if (key.key == MLX_KEY_D || key.key == MLX_KEY_RIGHT)
		(game->p_x)++;
	ft_printf("Movements: %d\r", ++(game->move_count));
}

static int	valid_mov(mlx_key_data_t key, t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->map)
		return (0);
		
	x = game->p_x;
	y = game->p_y;
	
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_UP)
		y--;
	else if (key.key == MLX_KEY_A || key.key == MLX_KEY_LEFT)
		x--;
	else if (key.key == MLX_KEY_S || key.key == MLX_KEY_DOWN)
		y++;
	else if (key.key == MLX_KEY_D || key.key == MLX_KEY_RIGHT)
		x++;
	else
		return (0);
	
	// Check bounds
	if (y < 0 || y >= game->map_height || x < 0)
		return (0);
	if (!game->map[y] || x >= (int)ft_strlen(game->map[y]))
		return (0);
	
	// Check if it's a wall or space (both invalid for movement)
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (0);
	
	return (1);
}

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = param;
	if (!game)
		return;
		
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			return (mlx_close_window(game->mlx));
		
		if (valid_mov(key, game) == 1)
		{
			update_pos(key, game);
			printf("Player moved to: (%d, %d)\n", game->p_x, game->p_y);
		}
		
		// Update player position on screen
		if (game->p && game->p->count > 0)
		{
			game->p->instances[0].x = game->p_x * 100;
			game->p->instances[0].y = game->p_y * 100;
		}
	}
}