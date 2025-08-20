/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 18:54:36 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_textures	textures;

	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&game, 0, sizeof(t_game));
	if (!check_args(argc, argv))
		return (1);
	store_map(&map, &textures, argv);
	check_map(&map);
	check_path_closed(&map);
	if (map.x_len > 38 || map.y_len > 20)
		ft_error("Map too big for this screen", &map, &game);
	game.p_x = map.p_x;
	game.p_y = map.p_y;
	game.mlx = mlx_init((map.x_len * 100), (map.y_len * 100), "Cube_3D", false);
	if (!game.mlx)
		ft_error("Unable to initialized MLX", &map, &game);
	init_textures(&game, &map);
	display_map(&game, &map, -1, -1);
	game.map = map.map;
	mlx_key_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	return (0);
}
