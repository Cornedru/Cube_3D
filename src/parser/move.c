/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 18:56:37 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"


static void	add_collectible(t_game *game)
{
	size_t	i;
	int		collectible_x;
	int		collectible_y;

	game->c_count--;
	game->map[game->p_y][game->p_x] = '0';
	i = 0;
	while (i < game->c->count)
	{
		collectible_x = game->c->instances[i].x;
		collectible_y = game->c->instances[i].y;
		if (collectible_x == game->p_x * 100 && collectible_y == game->p_y
			* 100)
		{
			game->c->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

static void	check_win(t_game *game)
{
	char	pos;

	pos = game->map[game->p_y][game->p_x];
	if (pos == 'C')
		add_collectible(game);
	if (pos == 'E' && game->c_count == 0)
		return (ft_printf("\nYou win, ggwp!\n"), mlx_close_window(game->mlx));
}

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
	check_win(game);
}

static int	valid_mov(mlx_key_data_t key, t_game *game)
{
	int	x;
	int	y;

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
	if (game->map[y][x] == '1')
		return (0);
	if (game->map[y][x] == 'E' && game->c_count > 0)
		return (0);
	return (1);
}

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_game	*game;

	game = param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_ESCAPE)
			return (mlx_close_window(game->mlx));
		if (valid_mov(key, game) == 1)
			update_pos(key, game);
		game->p->instances[0].x = game->p_x * 100;
		game->p->instances[0].y = game->p_y * 100;
	}
}
