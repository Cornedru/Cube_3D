/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 18:56:17 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void	display_map(t_game *game, t_map *map, int x, int y)
{
	while (map->map[++y] && y < map->y_len)
	{
		x = -1;
		while (map->map[y][++x] && x < map->x_len)
		{
			if (map->map[y][x] == '1')
				if (mlx_image_to_window(game->mlx, game->wall, x * 100, y
						* 100) < 0)
					ft_error("Cannot display wall", map, game);
			if (map->map[y][x] == 'P')
				if (mlx_image_to_window(game->mlx, game->p, map->p_x * 100,
						map->p_y * 100) < 0)
					ft_error("Cannot display player", map, game);
			if (map->map[y][x] == 'E')
				if (mlx_image_to_window(game->mlx, game->door, x * 100, y
						* 100) < 0)
					ft_error("Cannot display exit", map, game);
			if (map->map[y][x] == 'C')
				if (mlx_image_to_window(game->mlx, game->c, x * 100, y
						* 100) < 0)
					ft_error("Cannot display collectible", map, game);
		}
	}
}

static mlx_image_t	*init_img(char *path, t_game *game)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(game->mlx, texture);
	if (!img)
	{
		mlx_delete_texture(texture);
		return (NULL);
	}
	mlx_delete_texture(texture);
	return (img);
}

void	init_textures(t_game *game, t_map *map)
{
	game->p = init_img("./textures/n(1).png", game);
	if (!game->p)
		ft_error("Failed to load player texture.", map, game);
	game->c = init_img("./textures/g(1).png", game);
	if (!game->c)
		ft_error("Failed to load collectible texture.", map, game);
	game->wall = init_img("./textures/b(1).png", game);
	if (!game->wall)
		ft_error("Failed to load wall texture.", map, game);
	game->door = init_img("./textures/B(1).png", game);
	if (!game->door)
		ft_error("Failed to load exit texture.", map, game);
}
