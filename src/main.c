/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/08/28 03:46:06 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

void debug_print_map(t_game *g)
{
    printf("=== MAP DEBUG ===\n");
    printf("Map dimensions: %d x %d\n", g->map->x_len, g->map->y_len);
    printf("Player position: (%d, %d)\n", g->map->p_x, g->map->p_y);
    for (int y = 0; y < g->map->y_len; y++)
    {
        printf("Line %2d [len=%zu]: '", y, ft_strlen(g->map->map[y]));
        for (int x = 0; g->map->map[y][x]; x++)
        {
            if (g->map->map[y][x] == ' ')
                printf("_");
            else
                printf("%c", g->map->map[y][x]);
        }
        printf("'\n");
    }
    printf("=== END DEBUG ===\n");
}

int	main(int argc, char **argv)
{
	t_game	g;

	ft_memset(&g, 0, sizeof(t_game));
	g.map = gc_malloc(sizeof(t_map));
	g.pl = gc_malloc(sizeof(t_player));
	if (!check_args(argc, argv))
		return (1);

	// Map & Player
	store_map(&g, argv);
	debug_print_map(&g);
	check_map(&g);
	check_path_closed(g.map);
	// ft_printf("Map dimensions: %d x %d\n", g.map->x_len, g.map->y_len);

	init_player_direction(&g);
	// printf("----------------\nplayer:\n");
	// printf("- pos_x = %f\n- pos_y = %f\n- start dir: %c\n", g->pl->pos_x, g->pl->pos_y, g->pl->start_dir);
	// printf("----------------\n");

	init_game(&g);

	gc_destroy();
	return (0);
}
