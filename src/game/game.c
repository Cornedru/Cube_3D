/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:10:55 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 00:54:36 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

static void	game_loop(void *param)
{
	t_game	*g;

	g = param;
	if (!g)
		return ;
	update_player_state(g);
	raycast_loop(g);
}

static void	key_hook(mlx_key_data_t key, void *param)
{
	t_game	*g;
	bool	is_pressed;

	g = param;
	if (!g)
		return ;
	if (key.action == MLX_PRESS || key.action == MLX_RELEASE)
	{
		is_pressed = (key.action == MLX_PRESS);
		if (key.key == MLX_KEY_W)
			g->pl->keys.w = is_pressed;
		else if (key.key == MLX_KEY_S)
			g->pl->keys.s = is_pressed;
		else if (key.key == MLX_KEY_A)
			g->pl->keys.a = is_pressed;
		else if (key.key == MLX_KEY_D)
			g->pl->keys.d = is_pressed;
		else if (key.key == MLX_KEY_LEFT)
			g->pl->keys.left = is_pressed;
		else if (key.key == MLX_KEY_RIGHT)
			g->pl->keys.right = is_pressed;
	}
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(g->mlx);
}

int	init_game(t_game *g)
{
	g->mlx = mlx_init(g->res_w, g->res_h, "Cub3D", false);
	if (!g->mlx)
		return (ft_error("MLX: Unable to initialize", g->map, g), EXIT_FAILURE);
	load_textures(g);
	g->ceiling_hex = rgb_to_hexa_color(g->textures->ceiling.r,
			g->textures->ceiling.g, g->textures->ceiling.b,
			g->textures->ceiling.a);
	g->floor_hex = rgb_to_hexa_color(g->textures->floor.r, g->textures->floor.g,
			g->textures->floor.b, g->textures->floor.a);
	g->img = mlx_new_image(g->mlx, g->res_w, g->res_h);
	if (!(g->img))
		return (mlx_close_window(g->mlx), ft_error("MLX: Cannot create image",
				g->map, g), EXIT_FAILURE);
	if (mlx_image_to_window(g->mlx, g->img, 0, 0) == -1)
		return (mlx_close_window(g->mlx), ft_error("MLX: Cannot display image",
				g->map, g), EXIT_FAILURE);
	mlx_loop_hook(g->mlx, &game_loop, g);
	mlx_key_hook(g->mlx, &key_hook, g);
	mlx_loop(g->mlx);
	mlx_delete_image(g->mlx, g->img);
	mlx_terminate(g->mlx);
	return (EXIT_SUCCESS);
}
