/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/27 22:40:46 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

/* void	display_map(t_game *game, t_map *map, int x, int y)
{
	char	current_char;

	while (map->map[++y] && y < map->y_len)
	{
		x = -1;
		while (map->map[y][++x] && x < map->x_len)
		{
			current_char = map->map[y][x];
			if (current_char == '1')
			{
				if (mlx_image_to_window(game->mlx, game->wall, x * 100, y * 100) < 0)
					ft_error("Cannot display wall", map, game);
			}
		}
	}
	if (mlx_image_to_window(game->mlx, game->p, map->p_x * 100, map->p_y * 100) < 0)
		ft_error("Cannot display player", map, game);
} */

/* static mlx_image_t	*init_img(char *path, t_game *game)
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
} */

/* void	init_textures(t_game *game, t_map *map)
{
	game->p = init_img("./textures/n(1).png", game);
	if (!game->p)
		ft_error("Failed to load player texture.", map, game);
	
	game->wall = init_img("./textures/b(1).png", game);
	if (!game->wall)
		ft_error("Failed to load wall texture.", map, game);
} */
