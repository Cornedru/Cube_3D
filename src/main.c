/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/20 15:11:42 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&game, 0, sizeof(t_game));
	if (!check_args(argc, argv))
		return (1);
	// if (!parse_file(argv[1], &game))
	// 	return (1);
	store_map(&map, argv);
	check_map(&map);
	check_path_closed(&map);
	if (map.x_len > 38 || map.y_len > 20)
		ft_error("Map too big for this screen", &map, &game);
	game.p_x = map.p_x;
	game.p_y = map.p_y;
	game.mlx = mlx_init((map.x_len * 100), (map.y_len * 100), "so_long", false);
	if (!game.mlx)
		ft_error("Unable to initialized MLX", &map, &game);
	printf("\nParsing ok\n");
	return (0);
}
