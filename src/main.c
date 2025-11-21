/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oligrien <oligrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:51:24 by oligrien          #+#    #+#             */
/*   Updated: 2025/10/22 04:32:14 by oligrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"

int	main(int argc, char **argv)
{
	t_game	g;

	ft_memset(&g, 0, sizeof(t_game));
	g.res_w = WIN_W;
	g.res_h = WIN_H;
	g.map = gc_malloc(sizeof(t_map));
	g.pl = gc_malloc(sizeof(t_player));
	if (!check_args(&g, argc, argv))
		return (1);
	store_map(&g, argv);
	check_map(&g);
	check_path_closed(g.map);
	init_player_direction(&g);
	init_game(&g);
	gc_destroy();
	return (0);
}
