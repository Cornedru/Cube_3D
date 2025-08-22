/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <ndehmej@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/22 02:34:24 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void debug_print_map(t_map *map)
{
    printf("=== MAP DEBUG ===\n");
    printf("Map dimensions: %d x %d\n", map->x_len, map->y_len);
    printf("Player position: (%d, %d)\n", map->p_x, map->p_y);
    for (int y = 0; y < map->y_len; y++)
    {
        printf("Line %2d [len=%zu]: '", y, ft_strlen(map->map[y]));
        for (int x = 0; map->map[y][x]; x++)
        {
            if (map->map[y][x] == ' ')
                printf("_");
            else
                printf("%c", map->map[y][x]);
        }
        printf("'\n");
    }
    printf("=== END DEBUG ===\n");
}

int	main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_textures	textures;

	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&textures, 0, sizeof(t_textures));
	if (!check_args(argc, argv))
		return (1);
	store_map(&map, &textures, argv);
	debug_print_map(&map);
	check_map(&map);
	check_path_closed(&map);
	if (map.x_len > 38 || map.y_len > 20)
		ft_error("Map too big for this screen", &map, &game);
	game.p_x = map.p_x;
	game.p_y = map.p_y;
	game.map_width = map.x_len;
	game.map_height = map.y_len;
	game.textures = &textures;
	ft_printf("Map dimensions: %d x %d\n", map.x_len, map.y_len);
	ft_printf("Player spawn: (%d, %d)\n", game.p_x, game.p_y);
	game.mlx = mlx_init((map.x_len * 100), (map.y_len * 100), "Cube_3D", false);
	if (!game.mlx)
		ft_error("Unable to initialized MLX", &map, &game);
	init_textures(&game, &map);
	display_map(&game, &map, -1, -1);
	game.map = map.map;
	ft_printf("Starting MLX loop. Use WASD or arrow keys to move, ESC to quit.\n");
	mlx_key_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	delete_texture_img(&game);
	mlx_terminate(game.mlx);
	gc_destroy();
	return (0);
}